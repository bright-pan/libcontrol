#include "PIDcontroller.h"
#include "Types.h"
#include "usart.h"
#include "ascii.h"
#include <avr/io.h>
#include <avr/interrupt.h>

//In this simple example, the single job of the controller is to determine the coefficients of a single
//external object. Possibilities: RLC circuit, heater-in-a-box.
//target: atmega168, 8MHz nominal
//output: OC0A
//input: ADC0

const processValue_t G_maxProcessValue = -1;	//as type is unsigned, this corresponds to the MAX value
const processValue_t G_setpoint = 0x7fff;	//Vcc/2 - set this according to application
const processValue_t G_critical = 0xaaaa;	//Vcc*(2/3) - set this according to application
volatile int8_t g_alarm = 0;
volatile timeUs_t time = 0;

void init(void);
void set(processValue_t in);
processValue_t get(void);
processValue_t setp(void);
void super(processValue_t *inout);
timeUs_t getTime(void);
void handleError(error_t e);
processValue_t ReadADC(uint8_t ch);

void commandPidRun(void);
void commandPidRun(void);
void commandReportStatus(void);
void commandPidCalibrate(void);

#define PID_CALIBRATE ASCII_PRINTABLE_Z
#define PID_RUN ASCII_PRINTABLE_X
#define STEP_RUN ASCII_PRINTABLE_C
#define REPORT_STATUS ASCII_PRINTABLE_V
#define ERROR_OCCURED ASCII_CONTROL_DEL
#define START_OF_TEXT ASCII_CONTROL_STX
#define END_OF_TEXT ASCII_CONTROL_ETX
#define ACK ASCII_CONTROL_ACK
#define ERROR_UNKNOWN_COMMAND 255

#define DEBUG_PRINT(X) 	USARTtransmitBlock((unsigned char *)&X, sizeof(X));

//send ENQ
//wait for a command
//execute command
//return the return code
void main(void){
	error_t ret;
	unsigned char command;
	processValue_t m;

	init();
	sei();

	while(1){
	//ready - wait for a command
	USARTtransmit(ASCII_CONTROL_ENQ);
	ret = USARTreceive(&command);		//blocking
	handleError(ret);
	USARTtransmit(ACK);
	processValue_t temp;

	switch(command){
	//create a PID controller
	//run calibration
	//stream the report
	case PID_CALIBRATE:
		temp = get();	//adc test
		DEBUG_PRINT(temp)
		//commandPidCalibrate();
		break;

	//run PID with loaded gains and hardcoded frequency
	case PID_RUN:
		USARTtransmit(TCNT0);



//		set(20000);
		//handleError(ERROR_NOT_IMPLEMENTED);
		//USARTtransmit(ASCII_PRINTABLE_X);
		break;

	//perform a step experiment with the passed magnitude
	case STEP_RUN:
		temp = 1000;
		DEBUG_PRINT(temp);
//		handleError(ERROR_NOT_IMPLEMENTED);		
//		USARTtransmit(ASCII_PRINTABLE_C);
		break;

	//report memory usage
	case REPORT_STATUS:
		handleError(ERROR_NOT_IMPLEMENTED);		
		USARTtransmit(ASCII_PRINTABLE_V);
		break;
	default:
		handleError(ERROR_UNKNOWN_COMMAND);
	}
	};//while(1);
}

void commandPidCalibrate(void){
USARTtransmit(ASCII_PRINTABLE_a);
	PID_o *pid;
	PIDconfig_s pidConfig;
	error_t ret;
	
	pidConfig.setter = &set;
	pidConfig.getter = &get;
	pidConfig.getTimeUs = &getTime;
	pidConfig.setpoint = &setp;
	pidConfig.supervisor = &super;
	pidConfig.maxSafePlantOutput = G_maxProcessValue;	
	ret = PIDcreate(pid, &pidConfig);
	handleError(ret);
USARTtransmit(ASCII_PRINTABLE_b);
	//run calibration
	ret = PIDcalibrateInitialGuess(pid);
	handleError(ret);
USARTtransmit(ASCII_PRINTABLE_c);
	//report
	USARTtransmit(START_OF_TEXT);
	USARTtransmitBlock((unsigned char*)&(pid->report), sizeof(pid->report));
	USARTtransmit(END_OF_TEXT);
USARTtransmit(ASCII_PRINTABLE_d);
	PIDdestroy(pid);
USARTtransmit(ASCII_PRINTABLE_e);
}

void commandPidRun(void){
}

void commandStepRun(void){
}

void commandReportStatus(void){
}

void handleError(error_t e){
	if(e){
		USARTtransmit(ERROR_OCCURED);
		USARTtransmit(e);

		//TODO: maybe dump memory and registers

//		while(1);
	}
}

void init(void){
	//ports
	DDRB = 0xff;	//out
//	DDRA = 0x0;	//in

	//pwm
	TCCR0A = (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//fast pwm, no clock prescaling, output on PB3
	TCCR0B = (1<<WGM02) | (1<<CS00);
	OCR0A = 0;	//safe output: 0 volts

	//adc
	ADMUX = (1<<REFS0);		//range [0 - Vcc], free running mode
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//prescaler 128
//	ADCSRA = (1<<ADSC);	//start 

	//time
	TCCR1B = (1<<CS11);	//tick every us
	TIMSK1 = (1<<TOIE1);	//interrupt on oveflow

	USARTinit();
}	

ISR(TIMER1_OVF_vect){
	time += 0xffff;
}

void set(processValue_t in){
	OCR0A = 0xff;
	//OCR0A = in / 255;
}

processValue_t get(void){
	processValue_t t = ReadADC(0);
	return t<<6;
}

processValue_t setp(){
	return G_setpoint;
}

void super(processValue_t *inout){
	if (*inout > G_critical){
		*inout = 3;
		g_alarm = 1;
	}
}

timeUs_t getTime(){
	return time + TCNT1;
}

processValue_t ReadADC(uint8_t ch)
{
   //Select ADC Channel ch must be 0-7
   ch=ch&0b00000111;
   ADMUX|=ch;

   //Start Single conversion
   ADCSRA|=(1<<ADSC);

   //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it
   //Note you may be wondering why we have write one to clear it
   //This is standard way of clearing bits in io as said in datasheets.
   //The code writes '1' but it result in setting bit to '0' !!!

   ADCSRA|=(1<<ADIF);

   return(ADC);
}
