/*
 * Reel_Controller.cpp
 *
 * Created: 2/28/2013 10:10:47 PM
 *  Author: Anthony
 */ 

#include "Configuration.h"

#include <avr/io.h>
#include <util/delay.h>

#include "Pin.h"
#include "usitwislave.h"
#include "Reel_Controller.h"
#include "analog.h"
#include "Stepper.h"

Stepper *stepperArray[8];
uint16_t peakVals[8];

int main(void)
{	
	init();
	
	RED_PIN.setValue(true);

	// Delay between instantiations to avoid ISR overloading
	Stepper zero = Stepper (EN0, STEP0, DIR0);  // Stepper (EN0, STEP0, DIR0)
	_delay_ms(1);
	Stepper one = Stepper (EN1, STEP1, DIR1);
	_delay_ms(1);
	Stepper two = Stepper (EN2, STEP2, DIR2);
	_delay_ms(1);
	Stepper three = Stepper (EN3, STEP3, DIR3);
	_delay_ms(1);
	Stepper four = Stepper (EN4, STEP4, DIR4);
	_delay_ms(1);
	Stepper five = Stepper (EN5, STEP5, DIR5);
	_delay_ms(1);
	Stepper six = Stepper (EN6, STEP6, DIR6);
	_delay_ms(1);
	Stepper seven = Stepper (EN7, STEP7, DIR7);
	
	stepperArray[0] = &zero;
	stepperArray[1] = &one;
	stepperArray[2] = &two;
	stepperArray[3] = &three;
	stepperArray[4] = &four;
	stepperArray[5] = &five;
	stepperArray[6] = &six;
	stepperArray[7] = &seven;
	startSteppers();
	
	for(uint8_t i=0; i<8; i++){				// Initialize, backing up a hole for re-homing
		addStepper(stepperArray[i]);
		stepperArray[i]->setSpeed(CRUISE);
		stepperArray[i]->setDirection(BWD);
		stepperArray[i]->takeSteps(905);
		stepperArray[i]->setDirection(FWD);
	}

	RED_PIN.setValue(false);
	YEL_PIN.setValue(true);
	
	// Home reels (record peak values for calibration as well)
	uint16_t pk;
	uint16_t last;
	uint16_t timeout;
	for (uint8_t i = 0; i < 8; i++){
		analog::set_channel(i);
		stepperArray[i]->enable();
		pk = 0;
		last = 0;
		timeout = 0;
		while(pk < last + NOISE){		// 15 for noise (73mV). Typical peak is 2.5V (or 512 from ADC).
			stepperArray[i]->takeSteps(5);
			last = analog::read_once();
			if (last > pk){
				pk = last;
			}
			timeout++;
			if (timeout > 300){
				break;
			}
		}
		if (timeout < 299){
			db_pulse();			// Pulse 1: This is the channel's peak value.
			peakVals[i] = pk;
			locate_next(i);		// Pulse 2-5: Find center of next hole and home in on it.
		}
	}
	
	YEL_PIN.setValue(false);
	GRN_PIN.setValue(true);
	
	usi_twi_slave(SLAVE_ADDRESS, 0, handle_twi, idle);		// Never returns
}

void handle_twi(uint8_t buffer_size, volatile uint8_t input_buffer_length, 
				volatile const uint8_t *input_buffer, volatile uint8_t *output_buffer_length, 
				volatile uint8_t *output_buffer)
{
	YEL_PIN.setValue(true);
	uint8_t pri = input_buffer[0];
	uint8_t sec = input_buffer[1];
	if (pri <= 7){								// General stepper command
		switch(sec){
			case(STEP_ENABLE):{
				stepperArray[pri]->enable();
				break;
			}
			case(STEP_DISABLE):{
				stepperArray[pri]->disable();
				break;
			}
			case(STEP_FWD):{
				stepperArray[pri]->setDirection(0);
				break;
			}
			case(STEP_BWD):{
				stepperArray[pri]->setDirection(1);
				break;
			}
			case(NEXT_HOLE):{
				forward_hole(pri);
				break;
			}
			case(LAST_HOLE):{
				backward_hole(pri);
				break;
			}
			case(NEXT_BB):{
				forward_bb(pri);
				break;
			}
			case(LAST_BB):{
				backward_bb(pri);
				break;
			}
		}
	}
	
	else if (pri <= 15){								// Stepper speed command
		stepperArray[pri-8]->setSpeed(sec);
	}
		
	else if(pri == DEBUG_CTRL){					// Debug control command
		switch(sec){
			case(RED_ON):{
				RED_PIN.setValue(true);
				break;
			}
			case(GRN_ON):{
				GRN_PIN.setValue(true);
				break;
			}
			case(YEL_ON):{
				YEL_PIN.setValue(true);
				break;
			}
			case(RED_OFF):{
				RED_PIN.setValue(false);
				break;
			}
			case(GRN_OFF):{
				GRN_PIN.setValue(false);
				break;
			}
			case(YEL_OFF):{
				YEL_PIN.setValue(false);
				break;
			}
		}
	}
	
	YEL_PIN.setValue(false);
}	

void forward_hole(uint8_t stepper){
	locate_next(stepper);
}

void backward_hole(uint8_t stepper){
	stepperArray[stepper]->setDirection(true);
	stepperArray[stepper]->takeSteps(905);
}

void forward_bb(uint8_t stepper){
	stepperArray[stepper]->setDirection(false);
	stepperArray[stepper]->takeSteps(3632);			// 3621.6 in theory, this value is tuned b/c effective sprocket diameter is unpredictable.
}

void backward_bb(uint8_t stepper){
	stepperArray[stepper]->setDirection(true);
	stepperArray[stepper]->takeSteps(3632);
}

// This function will advance you to the next hole, with backlash compensation. Use 226.3 steps/mm.
// This is kind of messy because of the analog sensors and backlash in the motor and sprocket.
// From scoping, it looks like we could have around half a hole (750 um) of backlash!
// Procedure:
// 1) If we're currently over a hole, move up 6mm. Otherwise, 4mm. This puts us after target.
// 2) Move back until first threshold is found. Start step counting.
// 3) Move back until second threshold is found. End step counting; this is the adjusted hole width.
// 4) Move forward until first threshold is found.
// 5) Move forward half of the adjusted hole width. Done!
void locate_next(uint8_t chan){
	uint16_t sCount = 0;
	uint16_t aRead = 0;
	uint16_t thresh = peakVals[chan]/2;			// The hole width is measured from half-peak threshold.
	analog::set_channel(chan);
	analog::start();
	stepperArray[chan]->setDirection(FWD);
	stepperArray[chan]->setSpeed(CRUISE);
	if (analog::get() > thresh){				// Move up past the next hole
		stepperArray[chan]->takeSteps(1350);	
	} else {
		stepperArray[chan]->takeSteps(900);
	}
	stepperArray[chan]->setDirection(BWD);
	stepperArray[chan]->setSpeed(CRAWL);
	stepperArray[chan]->enable();
	while (aRead < thresh){					// Measure the hole width backwards
		aRead = analog::get();
	}
	db_pulse();									// Pulse 1: Begin measurement								// Pulse 2: We've reached first threshold
	stepperArray[chan]->takeSteps(10);			// Get clear of first threshold
	sCount = 10;								// We're measuring width now
	aRead = 1024;
	while (aRead > thresh){
		aRead = analog::get();
		stepperArray[chan]->takeSteps(1);
		sCount++;
	}
	db_pulse();									// Pulse 2: Reached second threshold
	stepperArray[chan]->takeSteps(30);			// Clear second threshold
	stepperArray[chan]->setDirection(FWD);		// Move forward past threshold to home position.
	stepperArray[chan]->enable();
	aRead = 0;
	while (aRead < thresh){						// Find second threshold going forward
		aRead = analog::get();
	}
	stepperArray[chan]->takeSteps(sCount/2);
	stepperArray[chan]->setSpeed(CRUISE);
	db_pulse(); // Pulse 4: We're home
	analog::stop();
}

void init(){
	// Initialize all stepper control pins to output
	DDRA |= 0xFF;	// All Port A
	DDRC |= 0xFF;	// All Port C
	DDRG |= 0x07;	// 0-2 Port G
	DDRD |= 0xFF;	// All Port D (Includes debug LEDs)
	
	// Define debug LEDs with neat Pin objects
	RED_PIN.setDirection(true);
	GRN_PIN.setDirection(true);
	YEL_PIN.setDirection(true);
	
	// Initialize all analog pins to input
	DDRF = 0x00;
	
	// Initialize analog settings
	analog::init(1);
}

void idle(void){
	return;
}

// This is an oscilloscope-detectable pulse on red LED for debugging.
void db_pulse(void){
	RED_PIN.setValue(true);
	_delay_ms(5);
	RED_PIN.setValue(false);
}