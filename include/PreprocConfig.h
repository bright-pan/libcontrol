//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#ifndef INC_LIB_CONTROL_PREPROC_CONFIG_H
#define INC_LIB_CONTROL_PREPROC_CONFIG_H

#include "Types.h"

//PID

//(feedthroughGain) * (feedback gain) = PID_CALIBRATION_INITIAL_GUESS_RELATIVE_GAIN
//				 	> 1	:	isntability
//					=	:	sustaindef oscillation
//					< 1	:	stability
//#define PID_CALIBRATION_INITIAL_GUESS_RELATIVE_GAIN 0.5
#define LIB_CONTROL_PID_CALIBRATION_INITIALGUESS_RELATIVE_GAIN (int2float(1) / 2)

//To capture debug dumps, define a print function and call it in this macro. If not
//defined or defined as empty, no machine instructions are generated.
#ifndef CONTROL_DEBUG_PRINT(X)
#define CONTROL_DEBUG_PRINT(X)
#endif

//Define values to various debugging events. Empty value generates no instrucions.
#ifndef CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_0
#define CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_0
#endif
#ifndef CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_1
#define CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_1
#endif
#ifndef CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_2
#define CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_2
#endif
#ifndef CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_3
#define CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_3
#endif
#ifndef CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_4
#define CONTROL_DEBUG_TRACE_STEP_BASIC_RUN_4
#endif

#endif	//INC_LIB_CONTROL_PREPROC_CONFIG_H
