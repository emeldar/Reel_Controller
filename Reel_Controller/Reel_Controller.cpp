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
#include "servo.h"
#include "analog.h"

uint16_t thresh;

int main(void)
{	
	RED_PIN.setDirection(true);
	GRN_PIN.setDirection(true);
	YEL_PIN.setDirection(true);
	
    asynctwi::init();
	asynctwi::setAddress(SLAVE_ADDRESS);
	asynctwi::attachSlaveRxEvent(handle_rx);
	servo::init_pwm();
	analog::init(1);

	while (1) {
		update_thresh();
		analog::set_channel(1);
		GRN_PIN.setValue(analog::read_once()>thresh);
	}
}

void handle_rx(uint8_t* buffer, int len)
{
	uint8_t lsb = buffer[0];
	uint8_t msb = buffer[1];

	servo::move_pwm(lsb);
}	

void update_thresh(void){
	analog::set_channel(0);
	thresh = analog::read_once();
}

void forward_holes(uint8_t holes){
	
}