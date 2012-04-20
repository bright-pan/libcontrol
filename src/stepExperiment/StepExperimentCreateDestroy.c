//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#include "StepExperiment.h"
#include <stdlib.h>

error_t stepExperimentCreate(stepExperiment_o * obj, const stepExperimentConfiguration_s *config){
	if(!config)
		return ERROR_NULL_POINTER;

	obj = (stepExperiment_o*)malloc(sizeof(stepExperiment_o));
	if(!obj)
		return ERROR_ALLOCATION_FAILURE;

	memcpy(&obj->config, config, sizeof(stepExperimentConfiguration_s));
	obj->report.memFootprint = sizeof(obj);
	return SUCCESS;
}
