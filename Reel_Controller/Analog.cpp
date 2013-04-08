/*
 * Photogate.cpp
 *
 * Created: 3/4/2013 1:37:53 PM
 *  Author: Anthony
 */ 

#include <avr/io.h>
#include "analog.h"

namespace analog {

void init(uint8_t channel){
	DIDR0 = 1<<channel;								// Disable digital input buffer (functionality) on channel pin
	ADMUX &= ~((1<<REFS1)|(1<<REFS0));				// AREF is used by default, set REFS1 and REFS0 low just in case
	set_channel(channel);							// Specify initialization channel
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));	// Prescale by 128, gives 156 KHz
}

void set_channel(uint8_t channel){
	ADMUX &= 0b11110000;
	ADMUX |= channel&(0b00001111);
	wait_for_completion();
}

uint16_t read_once(void)
{
	uint16_t res;
	ADCSRA |= (1<<ADEN)|(1<<ADSC);		// Turn ADC on and start a conversion
	wait_for_completion();
	res = ADCW;							// Read value
	ADCSRA &= ~(1<<ADSC);				// End read
	return res;
}

void start(void){
	ADCSRA |= (1<<ADATE);								// Enable auto trigger
	ADCSRB &=~((1<<ADTS0)|(1<<ADTS1)|(1<<ADTS2));		// Make sure free-running mode is selected
	ADCSRA |= (1<<ADEN);								// Turn on ADC
	ADCSRA |= (1<<ADSC);								// Start converting
}

uint16_t get(void){
	wait_for_completion();
	return ADCW;
}

void stop(void){
	wait_for_completion();
	ADCSRA &= ~(1<<ADEN);		// Turn off ADC
	ADCSRA &= ~(1<<ADATE);		// Disable auto trigger
}

void wait_for_completion(void){
	if (!(ADCSRA & (1 << ADSC))){		// Exit if there is no conversion in progress
		return;
	}
	ADCSRA|=(1<<ADIF);					// Clear flag
	while (!(ADCSRA & (1 << ADIF)));		// But if not, wait until completion flag is set
}

}