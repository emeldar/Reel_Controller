/*
 * Stepper.h
 * WIP, timers, classes
 *
 * Created: 3/8/2013 3:15:53 PM
 *  Author: Anthony
 */ 

#include "Pin.h"
#include <avr/io.h>

class Stepper {
	private:
		uint16_t ticks;
		uint16_t period;
		Pin en;
		Pin dir;
		Pin step;
		void tick_inc(void);
	public:
		Stepper(Pin en, Pin dir, Pin step);
        void setSpeed(uint16_t steps_per_s);
		void setDirection(uint8_t fwd);
        void disable(void);
        void enable(void);
		void stopTimer(void);
		void startTimer(void);
		
		friend void stepCounter(void);
};

void startSteppers(void);
void addStepper(Stepper *Stepper1);
void stepCounter(void);
