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
//If difference is within 2 * fivePercent(setpoint), output is considered to have settled.
error_t wait2settle(const step_o *const obj){
	processValue_t processOutput, processPreviousOutput;
	extremum_s lastExtremum;

	lastExtremum.type = minimum;
	lastExtremum.value = 0;
	processPreviousOutput = 0;

	do{
		processOutput = obj->config.getter();
		if(processOutput > obj->config.maxSafePlantOutput)
			return ERROR_PROCESS_OUTPUT_HIGHER_THAN_ALLOWED;

		if(lastExtremum.type == minimum){	//look for a maximum
			if(processOutput < processPreviousOutput){
				if(processOutput - lastExtremum.value < fivePercent(obj->report.settingPoint))
					return SUCCESS;
				else{
					lastExtremum.value = (processPreviousOutput + processOutput) / 2;
					lastExtremum.type = maximum;
				}
			}
		}else{			//look for a minimum
			if(processOutput > processPreviousOutput){
				if(lastExtremum.value - processOutput < fivePercent(obj->report.settingPoint))
					return SUCCESS;
				else{
					lastExtremum.value = (processPreviousOutput + processOutput) / 2;
					lastExtremum.type = minimum;
				}
			}
		}
		processPreviousOutput = processOutput;
	}while(1);
}
