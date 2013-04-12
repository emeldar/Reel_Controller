/*
 * Reel_Controller.cpp
 *
 * Created: 2/28/2013 10:10:47 PM
 *  Author: Anthony
 */ 
#define F_CPU  16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Pin.h"
#include "Configuration.h"
#include "Reel_Controller.h"
#include "analog.h"

int main(void)
{	
	init();
	analog::init(1);

	while (1) {
		analog::set_channel(1);
		GRN_PIN.setValue(analog::read_once()>THRESH);
	}
}

void handle_rx(uint8_t* buffer, int len)
{
	uint8_t lsb = buffer[0];
	uint8_t msb = buffer[1];

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