//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#include "atmel/pid.h"
#include "PIDcontroller.h"

#include <stdlib.h>
#include <string.h>

error_t PIDcreate(PID_o *obj, const PIDconfig_s *const config){
	if(!config)
		return ERROR_NULL_POINTER;

	obj = (PID_o*)malloc(sizeof(PID_o));
	if(!obj)
		return ERROR_ALLOCATION_FAILURE;

	memcpy((void*)&obj->config, (void*)config, sizeof(PIDconfig_s));
	obj->report.memFootprint = sizeof(obj);

	pid_Init(0, 0, 0, &obj->data.algData);

	return SUCCESS;
}


