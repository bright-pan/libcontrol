//Author//
//Miroslav Vitkov 2012
//sir.vorac(at)gmail(dot)com

//License//
//Beerware

#ifndef INC_LIB_CONTROL_TYPES_H
#define INC_LIB_CONTROL_TYPES_H

typedef uint16_t processValue_t;
typedef uint64_t timeUs_t;

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
#endif	//INC_LIB_CONTROL_TYPES_H
