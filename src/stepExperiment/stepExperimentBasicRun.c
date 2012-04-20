//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#include "preprocConfig.h"
#include "StepExperiment.h"

//measures if the system is stable and if so, what is the setpoint
error_t stepExperimentBasicRun(stepExperiment_o * obj, processValue stepSize){
	error_t status;
	obj->config.setter(stepSize);

 	status =  wait2settle(&obj->config);
	if(status != SUCCESS)
		return status;

	obj->report.stepSize = stepSize;
	obj->report.settingPoint = obj->config.getter();
	return SUCCESS;
}
