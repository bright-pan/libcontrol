//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#include "PreprocConfig.h"
#include "StepExperiment.h"

typedef enum{
	minimum = 0,
	maximum = 1,
}extremumType_e;
typedef int8_t extremumType_t;

typedef struct{
	extremumType_t type;
	processValue_t value;
}extremum_s;

//When direction of change switches, this is an extremum. Compare it's value with the prevous extremum recorded.
//If difference is within 2 * _FIVE_PERCENT(setpoint), output is considered to have settled.
error_t wait2settle(const step_o *const obj){
	uint16_t processOutput, processPreviousOutput;
	extremum_s lastExtremum;

	lastExtremum.type = minimum;
	lastExtremum.value = 0;
	processPreviousOutput = 0;

	do{
		processOutput = obj->config.getter();
		if(processOutput > obj->config.maxSafePlantOutput)
			return ERROR_PROCESS_OUTPUT_HIGHER_THAN_ALLOWED;

		if(lastExtremum.type == minimum){
			if(processOutput < processPreviousOutput){
				if(processOutput - lastExtremum.value < _FIVE_PERCENT(obj->report.settingPoint))
					return SUCCESS;
				else{
					lastExtremum.value = (processPreviousOutput + processOutput) / 2;
					lastExtremum.type = maximum;
				}
			}
			break;
		}else{
			if(processOutput > processPreviousOutput){
				if(lastExtremum.value - processOutput < _FIVE_PERCENT(obj->report.settingPoint))
					return SUCCESS;
				else{
					lastExtremum.value = (processPreviousOutput + processOutput) / 2;
					lastExtremum.type = minimum;
				}
			}
			break;	
		}
		processPreviousOutput = processOutput;
	}while(1);
}
