//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#ifndef INC_LIB_CONTROL_TYPES_H
#define INC_LIB_CONTROL_TYPES_H

#include <stdint.h>

typedef uint16_t processValue_t;
inline processValue_t fivePercent(processValue_t in){return in / 20;}
inline processValue_t ninetyFivePercent(processValue_t in){return (in - in / 20);}
#define LIB_CONTROL_MINUS_LN05 3

typedef uint32_t timeUs_t;	//1h 11m 30s

typedef enum error_{
	SUCCESS,
	ERROR_ALLOCATION_FAILURE,
	ERROR_NULL_POINTER,
	ERROR_PROCESS_OUTPUT_HIGHER_THAN_ALLOWED,
	EROR_PROCESS_OUTPUT_EXCEEDS_MAX_EVEN_FOR_ZERO_INPUT,


	ERROR_BAD_FUNCTION_PARAMETERS,
	ERROR_CONVERSION_OVERFLOW,
	ERROR_BUFFER_OVERFLOW,
	ERROR_BAD_EEPROM_ADDRESS,
	ERROR_NOISY_DATA,
	
	ERROR_NOT_INITIALIZED,
	ERROR_NOT_PROPERLY_DEINITIALIZED,
	
//minHAL:
	CPU_FREQ_NOT_SUPPORTED,



	ERROR_UNKNOWN,
	ERROR_NOT_IMPLEMENTED,
}error_e;
typedef int8_t error_t;

typedef enum _bool_{
	false = 0,
	true,
}_bool_e;
typedef int8_t _bool_t;

typedef uint16_t memAddr_t;


#define LIB_CONTROL_FLOAT_POINT_POSITION 16
typedef int32_t float_t;	//aka S32Q16
inline float_t int2float(processValue_t n){return ((float_t)n << LIB_CONTROL_FLOAT_POINT_POSITION);}
inline processValue_t float2int(float_t f){return (processValue_t)(f >> LIB_CONTROL_FLOAT_POINT_POSITION);}

#endif	//INC_LIB_CONTROL_TYPES_H
