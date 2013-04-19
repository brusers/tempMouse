#ifndef _PS2_H_
#define _PS2_H_

#include <avr/io.h>
		
void ps2_init(void);
void ps2_send_byte(int8_t sendByte);
void ps2_read_byte(void);
int8_t process_byte(void);

#define PS2_CLOCK_UP PORTD|=(1<<PORTD2)				// PS2 clock line high
#define PS2_CLOCK_DOWN PORTD&=~(1<<PORTD2)			// PS2 clock line low
#define PS2_DATA_UP PORTD|=(1<<PORTD1)				// PS2 data line high
#define PS2_DATA_DOWN PORTD&=~(1<<PORTD1)			// PS2 data line low

int16_t byteIn;



#endif
