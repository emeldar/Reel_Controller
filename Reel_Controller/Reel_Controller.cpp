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
#include "AsyncTwi.h"
#include "Pin.h"
#include "Configuration.h"
#include "Reel_Controller.h"

int main(void)
{
	RED_PIN.setDirection(true);
	GRN_PIN.setDirection(true);
	YEL_PIN.setDirection(true);
	
    asynctwi::init();
	asynctwi::setAddress(SLAVE_ADDRESS);
	asynctwi::attachSlaveRxEvent(handle_rx);
	
	while (1) {
		RED_PIN.setValue(true);
		_delay_ms(300);
		YEL_PIN.setValue(true);
		_delay_ms(300);
		GRN_PIN.setValue(true);
		_delay_ms(300);
		RED_PIN.setValue(false);
		_delay_ms(300);
		YEL_PIN.setValue(false);
		_delay_ms(300);
		GRN_PIN.setValue(false);
		_delay_ms(300);
	}
}

void handle_rx(uint8_t* buffer, int len)
{
	RED_PIN.setValue(true);
	YEL_PIN.setValue(true);
	GRN_PIN.setValue(true);
	_delay_ms(100);
	RED_PIN.setValue(false);
	YEL_PIN.setValue(false);
	GRN_PIN.setValue(false);
}	
