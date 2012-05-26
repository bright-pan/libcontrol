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

CONTROL_DEBUG_PRINT(CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_0);
	obj->config.setter(stepSize);
	obj->report.settingPoint = obj->config.maxSafePlantOutput;
CONTROL_DEBUG_PRINT(CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_1);
 	status =  wait2settle(obj);
CONTROL_DEBUG_PRINT(CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_2);
	if(status != SUCCESS)
		return status;
CONTROL_DEBUG_PRINT(CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_3);
	obj->report.stepSize = stepSize;
	obj->report.settingPoint = obj->config.getter();
CONTROL_DEBUG_PRINT(CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_4);
	return SUCCESS;
}
