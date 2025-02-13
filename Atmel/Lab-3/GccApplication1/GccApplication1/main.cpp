#define F_CPU 16000000UL // Define CPU frequency for delay.h

#include <avr/io.h>
#include <util/delay.h>

// Function prototypes
void initHardware();
void initADC();
int readADC(uint8_t channel);
void display(int adcValue);

int main(void) {
	int adcValue;

	// Initialize hardware and ADC
	initHardware();
	initADC();

	while (1) {
		// Read ADC value from channel 0
		adcValue = readADC(0);

		// Display the ADC value on the 7-segment displays
		display(adcValue);

		// Delay for 1 second
		_delay_ms(1000);
	}

	return 0;
}

void initHardware() {
	// Set PORTA and PORTC as output for 7-segment displays
	DDRA = 0xFF; // PORTA as output
	DDRC = 0xFF; // PORTC as output

	// Initialize PORTA and PORTC to 0
	PORTA = 0x00;
	PORTC = 0x00;
}

void initADC() {
	// Set the ADC reference voltage to AVCC (5V)
	ADMUX = (1 << REFS0);

	// Enable ADC and set pre-scaler to 128 (16MHz/128 = 125kHz)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

int readADC(uint8_t channel) {
	// Select ADC channel (0-7) and clear lower bits
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

	// Start ADC conversion
	ADCSRA |= (1 << ADSC);

	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC));

	// Return the ADC result
	return ADC;
}

void display(int adcValue) {
	// Split the ADC value into digits
	int thousands = adcValue / 1000;
	int hundreds = (adcValue % 1000) / 100;
	int tens = (adcValue % 100) / 10;
	int ones = adcValue % 10;

	// Display each digit on the 7-segment displays
	PORTC = (thousands << 4) | (hundreds & 0x0F); // PC7-PC4: thousands, PC3-PC0: hundreds
	PORTA = (tens << 4) | (ones & 0x0F);          // PA7-PA4: tens, PA3-PA0: ones
}