/*
 * Stepper.h
 * WIP, timers, classes
 *
 * Created: 3/8/2013 3:15:53 PM
 *  Author: Anthony
 */ 

#include "Pin.h"
#include <avr/io.h>

#define FWD false
#define BWD true

class Stepper {
	private:
		uint16_t ticks;
		uint16_t period;
		Pin en;
		Pin dir;
		Pin step;
		volatile uint16_t stepCount;
	public:
		Stepper(Pin en, Pin dir, Pin step);
        void setSpeed(uint8_t steps_per_s);
		void setDirection(uint8_t bwd);
        void disable(void);
        void enable(void);
		void stopTimer(void);
		void startTimer(void);
		void tick_inc(void);
		void takeSteps(uint16_t numSteps);
};

void startSteppers(void);
void addStepper(Stepper *Stepper1);
void stepCounter(void);
