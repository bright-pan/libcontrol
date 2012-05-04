//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

//Summary//
/* First, we estimate the first order model gain of the plant near the setpoint. Next, a P controller
 * is selected that satisfies kb < 1, where k - process gain, b - controller gain. Lastly,
 * I and D gains are selected according to an inverted Ziegler–Nichols table.
 *
 * This method is not reliable (actually I just made it up) and further refinement of the coefficients
 * is recommended. Stability is not guaranteed, neither is quality of transient processes.
 */

#include "PIDcontroller.h"
#include "stepExperiment.h"
#include "atmel/pid.h"
#include "preprocConfig.h"

//SCALING_FACTOR defined in atmel/pid.h
static inline int16_t PIDf2int16(float f){
	return ((int16_t)(f) * (SCALING_FACTOR));
}

error_t PIDcalibrateInitialGuess(PID_o *const pid){
	
	error_t ret;
	processValue_t magnitude;
	step_o *step;
	stepConfig_s cStep;	//TODO: fill up
	ret = stepCreate(step, &cStep);
	if(ret)
		return ret;
	pid->report.memFootprint += step->report.memFootprint;
	//step->report.gain = -1;	//stepCreate does that

	//1. Find linear gain at the setpoint. Use binary search.
	for(magnitude = 1; step->report.overshoot <= 0; magnitude *= 2){
		ret = stepBasicRun(step, magnitude);//magnitude is increased by a power of two, overshoot is observed
		if(ret != SUCCESS){
			//handle error
			return ret;
		}
		ret = stepSecondaryRun(step);	//blocking
		if(ret != SUCCESS){
			//handle error
			return ret;
		}
	}
	
	//2. Produce a P controller that drives the plant into the setpoint.
	//(feedthroughGain) * (feedback gain) 	> 1	:	isntability
	//					=	:	sustaindef oscillation
	//					< 1	:	stability
	pid->report.gains.p = PIDf2int16((PID_CALIBRATION_INITIAL_GUESS_RELATIVE_GAIN * (1.0 / step->report.gain)));
	
	//3. Using inverted Zeigler-Nichols table, select I and D gains.
	timeUs_t timeConstant = (1.0 / 3.0) * step->report.settingTimeUs;	//TODO: find/derive exact T for 5% setting
	pid->report.T = timeConstant;
	pid->report.gains.i = PIDf2int16(pid->report.gains.p * (2 / timeConstant));	//TODO: revise logick
	pid->report.gains.d = PIDf2int16(pid->report.gains.p * (timeConstant / 3));
	
	pid->report.memFootprint -= step->report.memFootprint;
	stepDestroy(step);
	return SUCCESS;
}
