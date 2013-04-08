/*
 * Photogate.h
 *
 * Created: 3/6/2013 3:12:52 PM
 *  Author: Anthony
 */ 

#include <avr/io.h>

namespace analog {

void init(uint8_t);

void set_channel(uint8_t);

uint16_t read_once(void);

void start(void);

uint16_t get(void);

void stop(void);

void wait_for_completion(void);

}