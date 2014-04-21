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
	TCCR2A |= (1<<CS21);		// Initialize Timer2 with 8x prescaler
	TIMSK2 |= (1<<TOIE2);				// Enable interrupt on overflow
	sei();								// Enable all interrupts
}

void addStepper(Stepper *Stepper1){
	stepperList[nSteppers] = Stepper1;
	nSteppers++;
}

ISR(TIMER2_OVF_vect) {
	stepperList[0]->tick_inc();
	stepperList[1]->tick_inc();
	stepperList[2]->tick_inc();
	stepperList[3]->tick_inc();
	stepperList[4]->tick_inc();
	stepperList[5]->tick_inc();
	stepperList[6]->tick_inc();
	stepperList[7]->tick_inc();
}

Stepper::Stepper(Pin en_in, Pin step_in, Pin dir_in){
	en = en_in;
	step = step_in;
	dir = dir_in;
	ticks = 0;
	stepCount = 0;
	disable();
	setDirection(true);
	setSpeed(1);
	disable();
}

void Stepper::setSpeed(uint8_t spd){
	period = 255/spd;	// Period from 1-255; from .07 to 17.3 mm/sec
}

void Stepper::setDirection(uint8_t bwd){
	dir.setValue(bwd);
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
			step.invPin();
			stepCount++;
			ticks = 0;
		}
}					

void Stepper::takeSteps(uint16_t numSteps){
	numSteps = 2*numSteps;		// Only steps on rising edge
	enable();
	stepCount = 0;
	sei();
	while(stepCount<=numSteps){}
	disable();
	cli();
}