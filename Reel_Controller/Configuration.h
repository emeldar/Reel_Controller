/*
 * Copyright 2013 Anthony McNicoll
 */

// TWI parameters
#define TWI_SDA					Pin(PortC,4)
#define SLAVE_ADDRESS 			0x12
#define I2C_SDA_PIN 			Pin(PortC,4)
#define I2C_SCL_PIN 			Pin(PortC,5)

// Hardware assignments
#define RED_PIN					Pin(PortD,0)
#define GRN_PIN					Pin(PortD,1)
#define YEL_PIN					Pin(PortD,2)

// Tuned parameters
#define THRESH					700

// Clock
#define F_CPU  16000000UL

// Primary Commands
// Note stepper channels are addressed by 0-7
#define DEBUG_CTRL				8

// Secondary Commands
#define RED_ON					1
#define GRN_ON					2
#define YEL_ON					3
#define RED_OFF					4
#define GRN_OFF					5
#define YEL_OFF					6