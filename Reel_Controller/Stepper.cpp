/*
 * Stepper.cpp
 * Limited use, but doesn't use timers!
 *
 * Created: 3/8/2013 3:15:53 PM
 *  Author: Anthony
 */ 

#include "Stepper.h"
#include <util/delay.h>
#include "Pin.h"
#include <avr/io.h>

#define		STEP_PIN	Pin(PortD,6)
#define		DIR_PIN		Pin(PortD,7)
#define		EN_PIN		Pin(PortD,5)
#define		FWD			0
#define		BWD			1

namespace stepper {
	uint32_t speed;					// Speed in steps per second
	
	void init_stepper(void){
		STEP_PIN.setDirection(true);
		DIR_PIN.setDirection(true);
		EN_PIN.setDirection(true);
		set_direction(FWD);
		set_speed(0);
	}

	void set_speed(uint16_t inspeed){
		speed = inspeed;
	}
	
	void set_direction(uint8_t dir){
		DIR_PIN.setValue(dir);
	}		
	
	void start(uint16_t pos){
	}
	
	void stop(uint16_t pos){
	}
	
	void take_steps(uint16_t steps){
		uint32_t del = 1000000/speed;
		for (uint16_t n=0; n<steps; n++){
			STEP_PIN.setValue(!STEP_PIN.getValue());
			_delay_us(del);
		}
	}
}