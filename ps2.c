#include "ps2.h"

void ps2_read_byte(void){
	EIMSK &= ~(1<<0);						// Disable INT0 interrupt
	byteIn = 0;
	
	for (int8_t i=0;i<10;i++){
		while(!(DDRD & (1<<DDD0)));			// Wait until clock is high
		while(DDRD & (1<<DDD0));			// Wait until clock is low
		byteIn |= (1<<i);					// Reads into int, correcting the bit order
	}
	EIMSK |= (1<<0);						// Enable INT0 interrupt
}


void ps2_send_byte(int8_t sendByte){
	EIMSK &= ~(1<<0);						// Disable INT0 interrupt
	DDRD |= (1<<DDD0);						// PS2 clock, set as output
	PORTD &= ~(1<<PORTD0);					// PS2 clock, set line low
	DDRD |= (1<<DDD1);						// PS2 data, set as output
	PORTD &= ~(1<<PORTD1);					// PS2 data, set line low
	DDRD &= ~(1<<DDD0);						// PS2 clock, set as input, to release line, mouse reads this as start bit
	
	for (uint8_t i=0;i<10;i++){
		while(DDRD & (1<<DDD0));			// Wait until clock is low
		if(sendByte & (1<<i))
			PORTD |= (1<<PORTD1);			// PS2 data, set line high, for a 1 bit
		else 
			PORTD &= ~(1<<PORTD1);			// PS2 data, set line low, for a 0 bit
		while(!(DDRD & (1<<DDD0)));			// Wait until clock is high
	}
	
	DDRD &= ~(1<<DDD1);						// PS2 data, set as input, to release line
	while(DDRD & (1<<DDD1));				// Wait until data is low, this is the mouse ACK bit
	while(!(DDRD & (1<<DDD0)));				// Wait until data is high, end of transmission
	EIMSK |= (1<<0);						// Enable INT0 interrupt
}


void ps2_init(void){
	_delay_ms(500);
}


int8_t process_byte(void){
	int8_t temp = (byteIn & 0xF0);			// Clearing most significant 8 bits, which includes the stop and parity
	byteIn = 0;	
	return temp;
}
