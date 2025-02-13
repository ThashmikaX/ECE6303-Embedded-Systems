#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define CHANNEL 0B00000000



void ConfigureADC(void);

int main(void)
{
	// Setting PORTD as output
	DDRD = 0B11111111;
	DDRB = 0B00100011;

	ConfigureADC();

	// Start ADC conversion
	ADCSRA |= 0B01000000;

	while (1)
	{
		// Blink LED at PORTB:PIN5
		PORTB |= 0B00100000;
		_delay_ms(500);
		PORTB &= 0B11011111;
		_delay_ms(500);
	}
}

void ConfigureADC(void)
{
	ADCSRA |= (1 << ADEN);  // Enable ADC
	ADCSRA |= 0B00000111;   // Selecting Prescaler value 128
	ADMUX &= 0B00001111;    // Enable AREF, clear previous channel selection
	ADMUX = (ADMUX & 0B11110000) | CHANNEL; // Select ADC channel 0

	// Enable interrupt
	ADCSRA |= (1 << ADIE);

	// Enable Free Running Mode
	ADCSRA |= (1 << ADATE);
	ADCSRB &= 0B11111000;

	sei(); // Enable Global Interrupts
}

ISR (ADC_vect)
{
	PORTD = ADC;
	PORTB |= (ADC>>8);
}