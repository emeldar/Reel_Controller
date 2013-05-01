/*
 * IncFile1.h
 *
 * Created: 2/28/2013 11:52:07 PM
 *  Author: Anthony
 */ 

int main(void);
void handle_twi(uint8_t buffer_size, volatile uint8_t input_buffer_length,
				volatile const uint8_t *input_buffer, volatile uint8_t *output_buffer_length,
				volatile uint8_t *output_buffer);
void init(void);
void idle(void);