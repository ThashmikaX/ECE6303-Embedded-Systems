#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= 0B00100000; // PORTB:PIN5 as output pin
	
	while (1)
	{
		PORTB |= 0B00100000; // Turn ON LED (PORTB:PIN5 high)
		_delay_ms(1000);      // Delay for 500 ms
		
		PORTB &= ~0B00100000; // Turn OFF LED (PORTB:PIN5 low)
		_delay_ms(1000);       // Delay for 500 ms
	}
}