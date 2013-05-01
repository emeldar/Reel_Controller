/*
 * Reel_Controller.cpp
 *
 * Created: 2/28/2013 10:10:47 PM
 *  Author: Anthony
 */ 

#include "global.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Configuration.h"
#include "Pin.h"
#include "usitwislave.h"
#include "Reel_Controller.h"
#include "analog.h"
#include "Stepper.h"

Stepper lights(RED_PIN, GRN_PIN, YEL_PIN);

int main(void)
{	
	init();
	GRN_PIN.setValue(true);
	//usi_twi_slave(SLAVE_ADDRESS, 0, handle_twi, idle);		// Never returns
}

void handle_twi(uint8_t buffer_size, volatile uint8_t input_buffer_length, 
				volatile const uint8_t *input_buffer, volatile uint8_t *output_buffer_length, 
				volatile uint8_t *output_buffer)
{
	uint8_t lsb = input_buffer[0];
	uint8_t msb = input_buffer[1];
	switch(lsb){						// Primary command
		case(DEBUG_CTRL):{
			switch(msb){
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
			break;
		}
		
		default:{
			
		}
	}
	_delay_ms(50);
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