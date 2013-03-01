/*
 * Copyright 2010 by Adam Mayer	 <adam@makerbot.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

// TWI stuff
#define TWI_SDA					Pin(PortC,4)
#define SLAVE_ADDRESS 			0x12
#define I2C_SDA_PIN 			Pin(PortC,4)
#define I2C_SCL_PIN 			Pin(PortC,5)

// Hardware assignments
#define RED_PIN					Pin(PortB,1)
#define GRN_PIN					Pin(PortB,2)
#define YEL_PIN					Pin(PortB,3)

// Clock
#define F_CPU  16000000UL
