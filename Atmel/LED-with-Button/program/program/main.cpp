#include <avr/io.h>
#define F_CPU 16000000UL

int main(void)
{
	/* Replace with your application code */
	DDRD &= 0B01111111; // Port D's pin7 is set to input
	DDRB |= 0800010000; //POrt B's pin4 is set to output
	while (1)
	{
		if (PIND & OB10000000)
		{
			PORTB=0B00010000; //make the port B's pin4 to high
		}else
		{
			PORTB &= 0B11101111;//make the port B's pin4 to low
		}
	}
}