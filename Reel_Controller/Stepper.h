/*
 * Stepper.h
 * Limited use, but doesn't use timers!
 *
 * Created: 3/8/2013 3:15:53 PM
 *  Author: Anthony
 */ 

#define F_CPU  16000000UL
#include <util/delay.h>
#include "Pin.h"
#include <avr/io.h>

namespace stepper {
	void init_stepper(void);

	void set_speed(uint16_t);
	
	void set_direction(uint8_t);
	
	void start(uint16_t);
	
	void stop(uint16_t);
	
	void take_steps(uint16_t);
	}