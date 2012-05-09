//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#include "PreprocConfig.h"
#include "StepExperiment.h"

//Measures if the system is stable and if so, what is the setpoint.
//Thiese are rough "quick and dirty" measurements.
//As we don't know the setting point, but need it in order to detect that the 
//process has settled within five percent, the maximum allowed plant
//output is used in it's place.
error_t stepBasicRun(step_o * obj, processValue_t stepSize){
	error_t status;

	obj->config.setter(stepSize);
	obj->report.settingPoint = obj->config.maxSafePlantOutput;
 	status =  wait2settle(obj);
	if(status != SUCCESS)
		return status;

	obj->report.stepSize = stepSize;
	obj->report.settingPoint = obj->config.getter();
	return SUCCESS;
}
