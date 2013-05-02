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

stepperArray = new *Stepper[8];
stepperArray[0] = new Stepper (RED_PIN, GRN_PIN, YEL_PIN);
stepperArray[1] = new one (RED_PIN, GRN_PIN, YEL_PIN);
stepperArray[2] = Stepper two (RED_PIN, GRN_PIN, YEL_PIN);
stepperArray[3] = Stepper three (RED_PIN, GRN_PIN, YEL_PIN);
stepperArray[4] = Stepper four (RED_PIN, GRN_PIN, YEL_PIN);
stepperArray[5] = Stepper five (RED_PIN, GRN_PIN, YEL_PIN);
stepperArray[6] = Stepper six (RED_PIN, GRN_PIN, YEL_PIN);
stepperArray[7] = Stepper seven (RED_PIN, GRN_PIN, YEL_PIN);


int main(void)
{	
	init();
	addStepper(&lights);
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
				RED_PIN.setValue(true);
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