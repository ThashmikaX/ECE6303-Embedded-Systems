#include <avr/io.h>
#define F_CPU 16000000UL

int main(void)
{
	/* Configure PORTD pin 3 as input */
	DDRD &= 0b11110111; // Clear bit 3 of DDRD to make it input (1 -> 0)
	
	/* Configure PORTB pin 5 as output (Arduino pin 13) */
	DDRB |= 0b00100000; // Set bit 5 of DDRB to make it output (0 -> 1)

	while (1)
	{
		/* Check if button connected to pin 3 is pressed (logic high) */
		if (PIND & 0b00001000) // Check bit 3 of PIND
		{
			PORTB |= 0b00100000; // Set bit 5 of PORTB to make LED on
		}
		else
		{
			PORTB &= 0b11011111; // Clear bit 5 of PORTB to make LED off
		}
	}
}
