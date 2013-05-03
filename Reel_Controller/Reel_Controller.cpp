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

Stepper *stepperArray[8];

int main(void)
{	
	// Delay between instantiations to avoid ISR overloading
	Stepper zero = Stepper (EN0, STEP0, DIR0);  // Stepper (EN0, STEP0, DIR0)
	_delay_ms(1);
	Stepper one = Stepper (EN1, STEP1, DIR1);
	_delay_ms(1);
	Stepper two = Stepper (EN2, STEP2, DIR2);
	_delay_ms(1);
	Stepper three = Stepper (EN3, STEP3, DIR3);
	_delay_ms(1);
	Stepper four = Stepper (EN4, STEP4, DIR4);
	_delay_ms(1);
	Stepper five = Stepper (EN5, STEP5, DIR5);
	_delay_ms(1);
	Stepper six = Stepper (EN6, STEP6, DIR6);
	_delay_ms(1);
	Stepper seven = Stepper (EN7, STEP7, DIR7);
	
	stepperArray[0] = &zero;
	stepperArray[1] = &one;
	stepperArray[2] = &two;
	stepperArray[3] = &three;
	stepperArray[4] = &four;
	stepperArray[5] = &five;
	stepperArray[6] = &six;
	stepperArray[7] = &seven;

	init();
	
	addStepper(stepperArray[0]);
	addStepper(stepperArray[1]);
	addStepper(stepperArray[2]);
	addStepper(stepperArray[3]);
	addStepper(stepperArray[4]);
	addStepper(stepperArray[5]);
	addStepper(stepperArray[6]);
	addStepper(stepperArray[7]);
	
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
				stepperArray[pri]->enable();
				break;
			}
			case(STEP_DISABLE):{
				stepperArray[pri]->disable();
				break;
			}
			case(STEP_FWD):{
				stepperArray[pri]->setDirection(1);
				break;
			}
			case(STEP_BWD):{
				stepperArray[pri]->setDirection(0);
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
	
	else if (pri <= 15){								// General stepper command
		stepperArray[pri-8]->setSpeed(sec);
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