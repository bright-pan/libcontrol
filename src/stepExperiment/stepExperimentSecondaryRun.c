//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#include "StepExperiment.h"

static processValue_t getLocalMaximum(const stepExperimentConfig_s *const P_params);

error_t stepExperimentRun(stepExperiment_o * obj){
	processValue_t processOutput, setpoint;
	timeUs_t t0, t1, t2, t3;
	
	//Firstly, turn off control until the process output settles.
	obj->config.setter(0);
	wait2settle(&obj->config);
	processOutput = obj->config.getter();
	obj->report.bias = processOutput;
	
	//Secondly, record t0 and perform a step change of the controller output;
	t0 = obj->config.getTimeUs();
	obj->config.setter(obj->report.stepSize);
	
	//Thirdly, measure pureDelayUs
	do{
		processOutput = obj->config.getter();
	}while(processOutput < _FIVE_PERCENT(obj->report.settingPoint));
	t1 = obj->config.getTimeUs();
	obj->report.pureDelayUs = t1 - t0;

	//Fourth, identify riseTimeUs.
	do{
		processOutput = obj->config.getter();
	}while(processOutput < _NINETY_FIVE_PERCENT(obj->report.settingPoint));
	t2 = obj->config.getTimeUs();
	obj->report.riseTimeUs = t2 - t1;
	
	//Fifth, get overshoot.
	obj->report.overshoot = ((1.0 * getLocalMaximum(&obj->config)) / setpoint) - 1.0;

	//Sixth, measure setting time
	wait2settle(&obj->config);
	t3 = obj->config.getTimeUs();
	obj->report.settingTimeUs = t3 - t2;
	
	//Seventh, record settingPoint, hopefully with higher accuracy than in the basic experiment.
	obj->report.settingPoint = obj->config.getter();
	
	//Eight, calculate gain
	obj->report.gain = obj->report.settingPoint / obj->report.stepSize;

	return SUCCESS;
}

static processValue_t getLocalMaximum(const stepExperimentConfig_s *const P_params){
	processValue_t processOutput, processPreviousOutput;
	
	do{
		processOutput = P_params->getter();
		if(processOutput < processPreviousOutput)
			return (processOutput + processPreviousOutput) / 2;
		processPreviousOutput = processOutput;
	}while(1);
}
