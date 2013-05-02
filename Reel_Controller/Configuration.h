/*
 * Copyright 2013 Anthony McNicoll
 */
// Clock
#define F_CPU        16000000

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

// Primary Commands
// Note stepper channel commands are addressed by 0-7
// Stepper speed settings are addressed by 8-15
// Stepper step increment commands are addressed 16-23

#define DEBUG_CTRL				255

// Secondary Commands
// General stepper commands, primary 0-7
#define STEP_ENABLE				1
#define STEP_DISABLE			2
#define STEP_FWD				3
#define STEP_BWD				4
#define NEXT_HOLE				5
#define LAST_HOLE				6

// Debug control commands, primary 50
#define RED_ON					1
#define GRN_ON					2
#define YEL_ON					3
#define RED_OFF					4
#define GRN_OFF					5
#define YEL_OFF					6

// Stepper Channel Definitions