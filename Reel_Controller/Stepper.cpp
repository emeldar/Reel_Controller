/*
 * Stepper.cpp
 * Rewriting to use timer 0.
 *
 * Created: 3/8/2013 3:15:53 PM
 *  Author: Anthony
 */ 

#include "Configuration.h"
#include "Stepper.h"
#include "Pin.h"
#include <avr/io.h>

Stepper::Stepper(Pin en_in, Pin dir_in, Pin step_in){
	en = en_in;
	dir = dir_in;
	step = step_in;
	en.setDirection(true);
	dir.setDirection(true);
	step.setDirection(true);
	disable();
	startTimer();
}

void Stepper::setSpeed(uint16_t steps_per_s){
	period = (F_CPU/1024)/(steps_per_s);
}

void Stepper::setDirection(uint8_t fwd){
	dir.setValue(fwd);
}

void Stepper::disable(void){
	en.setValue(true);
}

void Stepper::enable(void){
	en.setValue(false);
}

void Stepper::stopTimer(void){
	TCCR0A &= ~((1<<CS00)|(1<<CS02));	// Timer off
}

void Stepper::startTimer(void){
	TCCR0A |= (1<<CS00)|(1<<CS02);	// Prescaler = 1024
}