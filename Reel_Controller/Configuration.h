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
