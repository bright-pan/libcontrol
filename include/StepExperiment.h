//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

//RECOM: run in interrupt-free enviroment for time cosntants in the us and ms range

#ifndef LIB_CONTROL_STEP_EXPERIMENT_H_
#define LIB_CONTROL_STEP_EXPERIMENT_H_

//Includes//
#include "types.h"
#include "preprocConfig.h"

#include <stdlib.h>

//Typedefs//
typedef struct{
	void (*setter)(processValue_t);
	processValue_t (*getter)(void);
	timeUs_t (*getTimeUs)(void);
	processValue_t maxSafePlantOutput;
}stepExperimentConfig_s;

typedef struct{
	float gain;				// == setpoint / magnitude
	timeUs_t pureDelayUs;			// == time from step to increase of process output to  5% of setpoint
	timeUs_t riseTimeUs;			// == time from step to increase of process output to 95% of setpoint
	timeUs_t settingTimeUs;			// == time from step to when process output is stable to within 5% of setpoint
	float overshoot;			// == (max(responses[]) / setpoint) - 1
	processValue_t bias; 			// == process output when input is zero
	processValue_t settingPoint;		//plant output after transients have passed
	processValue_t stepSize;		//
	memAddr_t memFootprint;
}stepExperimentReport_s;

typedef struct{
}stepExperimentPrivateData_s;

typedef struct{
	const stepExperimentConfig_s config;
	stepExperimentReport_s report;
	stepExperimentPrivateData_s data;
	memAddr_t memFotprint;
}stepExperiment_o;

//Functions//
error_t stepExperimentCreate(stepExperiment_o * obj, const stepExperimentConfig_s *config);
void stepExperimentDestroy(stepExperiment_o * obj);

//measures if the system is stable and if so, what is the setpoint
error_t stepExperimentBasicRun(stepExperiment_o * obj, processValue_t stepSize);	

//performs detailed measurement, based on the data of the primary run
error_t stepExperimentSecondaryRun(stepExperiment_o * obj);	

//Block until process extremums deviate less than 5% from the setting point.
error_t wait2settle(const stepExperiment_o *const obj);

//////////////////////////// Implementation of inline functions ///////////////////////////////////////

inline void stepExperimentDestroy(stepExperiment_o *const obj){
	free(obj);
}

#endif	//LIB_CONTROL_STEP_EXPERIMENT_H_
