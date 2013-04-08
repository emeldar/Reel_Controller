/*
 * servo.h
 *
 * Created: 3/4/2013 12:51:01 PM
 *  Author: Anthony
 */ 

#define	SERVO_MAX			500		// 2ms
#define SERVO_MIN			250		// 1ms
#define SERVO_BIAS			-4
#define PWM_PIN					Pin(PortB,1)

namespace servo {

void init_pwm(void);
void move_pwm(uint16_t pos);

}