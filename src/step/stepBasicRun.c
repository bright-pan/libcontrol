//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#include "PreprocConfig.h"
#include "StepExperiment.h"

//measures if the system is stable and if so, what is the setpoint
error_t stepBasicRun(step_o * obj, processValue_t stepSize){
	error_t status;
	obj->config.setter(stepSize);

 	status =  wait2settle(obj);
	if(status != SUCCESS)
		return status;

	obj->report.stepSize = stepSize;
	obj->report.settingPoint = obj->config.getter();
	return SUCCESS;
}
