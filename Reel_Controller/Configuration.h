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
#define EN0						Pin(PortA,0)
#define STEP0					Pin(PortA,1)
#define DIR0					Pin(PortA,2)
#define EN1						Pin(PortA,3)
#define STEP1					Pin(PortA,4)
#define DIR1					Pin(PortA,5)
#define EN2						Pin(PortA,6)
#define STEP2					Pin(PortA,7)
#define DIR2					Pin(PortG,2)
#define EN3						Pin(PortC,7)
#define STEP3					Pin(PortC,6)
#define DIR3					Pin(PortC,5)
#define EN4						Pin(PortC,4)
#define STEP4					Pin(PortC,3)
#define DIR4					Pin(PortC,2)
#define EN5						Pin(PortC,1)
#define STEP5					Pin(PortC,0)
#define DIR5					Pin(PortG,1)
#define EN6						Pin(PortG,0)
#define STEP6					Pin(PortD,7)
#define DIR6					Pin(PortD,6)
#define EN7						Pin(PortD,5)
#define STEP7					Pin(PortD,4)
#define DIR7					Pin(PortD,3)