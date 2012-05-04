//Author//
//Miroslav Vitkov 2011
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#ifndef LIB_CONTROL_INC_PID_CONTOLLER_H_
#define LIB_CONTROL_INC_PID_CONTOLLER_H_

//Includes//
#include "atmel/pid.h" 
#include "types.h"
#include "preprocConfig.h"

#include <stdlib.h>

//Typedefs//
typedef struct{
	int16_t p;
	int16_t i;
	int16_t d;
}PIDgains_s;

typedef struct{
	void (*setter)(processValue_t);
	processValue_t (*getter)(void);
	timeUs_t (*getTimeUs)(void);
	processValue_t (*setpoint)(void);
	void (*supervisor)(processValue_t*);
}PIDconfig_s;

typedef struct{
	PIDgains_s gains;
	timeUs_t T;
	memAddr_t memFootprint;
}PIDreport_s;

typedef struct{
	pidData_t algData;
}PIDprivateData_s;

typedef struct{
	const PIDconfig_s config;
	PIDreport_s report;
	PIDprivateData_s data;
}PID_o;
	
//Functions//
error_t PIDcreate(PID_o *obj, const PIDconfig_s *const config);
inline void PIDdestroy(PID_o *obj);

//error_t PIDloadGains(PIDgains_s gains);	//TODO:
error_t PIDcalibrateInitialGuess(PID_o *const pid);	//fetch useful pid gains

inline void PIDinit(PID_o *obj);	//push loaded gains to the controller
void PIDrun(PID_o *obj);	//do one pid iteration

///////////////////// Implementation of inlined functions ////////////////////////////////////////////////
inline void  PIDinit(PID_o *obj){
	pid_Init(obj->report.gains.p, obj->report.gains.i, obj->report.gains.d, &obj->data.algData);
}

inline void  PIDdestroy(PID_o *obj){
	free(obj);
}

#endif //LIB_CONTROL_INC_PID_CONTOLLER_H_
