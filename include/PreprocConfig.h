//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#ifndef INC_LIB_CONTROL_PREPROC_CONFIG_H
#define INC_LIB_CONTROL_PREPROC_CONFIG_H

//PID

//(feedthroughGain) * (feedback gain) = PID_CALIBRATION_INITIAL_GUESS_RELATIVE_GAIN
//				 	> 1	:	isntability
//					=	:	sustaindef oscillation
//					< 1	:	stability
#define PID_CALIBRATION_INITIAL_GUESS_RELATIVE_GAIN 0.5

//ZN calibration table variant
//#define _PID_CALIBRATION_ORIGINAL
//#define _PID_CALIBRATION_LITTLE_OVERSHOOT
//#define _PID_CALIBRATION_NO_OVERSHOOT

#endif	//INC_LIB_CONTROL_PREPROC_CONFIG_H
