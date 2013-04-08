/*
 * servo.cpp
 * Limited use, allows 1 servo on PB1, uses timer 1
 *
 * Created: 3/1/2013 3:58:19 PM
 *  Author: Anthony
 */ 

#include <avr\io.h>
#include "servo.h"
#include "Pin.h"

namespace servo {

void init_pwm(void){
	PWM_PIN.setDirection(true);
	TCCR1A |= (1<<COM1A1)|(1<<WGM11);						//	Clear OC1A on Compare Match, set OC1A at BOTTOM
	TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);	//  Fast PWM, TOP = ICR1, CLKDIV = 7
	ICR1 = 4999;											//  20 ms period
	move_pwm(127);											//  Initialize to center
}

void move_pwm(uint16_t pos){
	if (-(SERVO_BIAS) < pos){
		pos = pos + (SERVO_BIAS);
	}
	OCR1A = SERVO_MIN + ((SERVO_MAX-SERVO_MIN)*pos)/256;
}

}