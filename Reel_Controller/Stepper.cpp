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
#include <avr/interrupt.h>

Stepper *stepperList[8];
uint8_t nSteppers;

// Add all steppers first
void startSteppers(void){
	TCCR2A |= (1<<CS20);		// Initialize Timer0 with no prescaler	
	TIMSK2 |= (1<<TOIE2);		// Enable interrupt on overflow
	sei();						// Enable all interrupts
}

void addStepper(Stepper *Stepper1){
	stepperList[nSteppers] = Stepper1;
	nSteppers++;
}

void stepCounter(void){
	uint8_t s;
	for (s = 0; s<=nSteppers; s++){
		stepperList[s]->tick_inc();
	}
}

ISR(TIMER2_OVF_vect) {
	stepCounter();
}

Stepper::Stepper(Pin en_in, Pin step_in, Pin dir_in){
	en = en_in;
	step = step_in;
	dir = dir_in;
	disable();
	setDirection(true);
	setSpeed(1);
	disable();
}

void Stepper::setSpeed(uint16_t steps_per_s){
	period = (31250/(steps_per_s));				// Assumes 8 bit overflow and 16 MHz clock
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

void Stepper::tick_inc(void){
	ticks++;
	if (ticks >= period){
		if (step.getValue()==false){
			step.setValue(true);
		} else {
			step.setValue(false);
		}
		ticks = 0;
	}
}					