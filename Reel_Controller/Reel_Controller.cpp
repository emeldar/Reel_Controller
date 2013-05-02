/*
 * Reel_Controller.cpp
 *
 * Created: 2/28/2013 10:10:47 PM
 *  Author: Anthony
 */ 

#include "Configuration.h"

#include <avr/io.h>
#include <util/delay.h>

#include "Pin.h"
#include "usitwislave.h"
#include "Reel_Controller.h"
#include "analog.h"
#include "Stepper.h"

Stepper stepperArray[] = {};

int main(void)
{	
	stepperArray[0] = Stepper (RED_PIN, GRN_PIN, YEL_PIN);
	stepperArray[1] = Stepper (EN1, STEP1, DIR1);
//	Stepper stepperArray[8] = {	Stepper (RED_PIN, GRN_PIN, YEL_PIN),
//								Stepper (EN1, STEP1, DIR1),
//								Stepper (EN2, STEP2, DIR2),
//								Stepper (EN3, STEP3, DIR3),
//								Stepper (EN4, STEP4, DIR4),
//								Stepper (EN5, STEP5, DIR5),
//								Stepper (EN6, STEP6, DIR6),
//								Stepper (EN7, STEP7, DIR7)  };
	init();
	addStepper(&stepperArray[0]);
	addStepper(&stepperArray[1]);
	startSteppers();
	usi_twi_slave(SLAVE_ADDRESS, 0, handle_twi, idle);		// Never returns
}

void handle_twi(uint8_t buffer_size, volatile uint8_t input_buffer_length, 
				volatile const uint8_t *input_buffer, volatile uint8_t *output_buffer_length, 
				volatile uint8_t *output_buffer)
{
	uint8_t pri = input_buffer[0];
	uint8_t sec = input_buffer[1];
	if (pri <= 7){								// General stepper command
		switch(sec){
			case(STEP_ENABLE):{
				//stepperArray[pri].enable();
				break;
			}
			case(STEP_DISABLE):{
				GRN_PIN.setValue(true);
				break;
			}
			case(STEP_FWD):{
				YEL_PIN.setValue(true);
				break;
			}
			case(STEP_BWD):{
				RED_PIN.setValue(false);
				break;
			}
			case(NEXT_HOLE):{
				GRN_PIN.setValue(false);
				break;
			}
			case(LAST_HOLE):{
				YEL_PIN.setValue(false);
				break;
			}
		}
	}	
		
	else if(pri == DEBUG_CTRL){					// Debug control command
		switch(sec){
			case(RED_ON):{
				RED_PIN.setValue(true);
				break;
			}
			case(GRN_ON):{
				GRN_PIN.setValue(true);
				break;
			}
			case(YEL_ON):{
				YEL_PIN.setValue(true);
				break;
			}
			case(RED_OFF):{
				RED_PIN.setValue(false);
				break;
			}
			case(GRN_OFF):{
				GRN_PIN.setValue(false);
				break;
			}
			case(YEL_OFF):{
				YEL_PIN.setValue(false);
				break;
			}
		}
	}
}	

void forward_holes(uint8_t holes){
	
}

void init(){
	// Initialize all stepper control pins to output
	DDRA |= 0xFF;	// All Port A
	DDRC |= 0xFF;	// All Port C
	DDRG |= 0x07;	// 0-2 Port G
	DDRD |= 0xFF;	// All Port D (Includes debug LEDs)
	
	// Re-do debug LEDs with neat Pin objects
	RED_PIN.setDirection(true);
	GRN_PIN.setDirection(true);
	YEL_PIN.setDirection(true);
	
	// Initialize all analog pins to input
	DDRF = 0x00;
}

void idle(void){
	return;
}