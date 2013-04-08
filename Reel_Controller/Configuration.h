/*
 * Copyright 2013 Anthony McNicoll
 */

// TWI stuff
#define TWI_SDA					Pin(PortC,4)
#define SLAVE_ADDRESS 			0x12
#define I2C_SDA_PIN 			Pin(PortC,4)
#define I2C_SCL_PIN 			Pin(PortC,5)

// Hardware assignments
#define RED_PIN					Pin(PortB,4)
#define GRN_PIN					Pin(PortB,2)
#define YEL_PIN					Pin(PortB,3)

// Clock
#define F_CPU  16000000UL
