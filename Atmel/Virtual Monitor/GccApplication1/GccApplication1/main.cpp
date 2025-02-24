#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_Value ((F_CPU/16/BAUD)-1)
#include <avr/io.h>
#include <unistd.h>
#define _delay_ms(ms) usleep((ms) * 1000)

void configUart(void) {
	UBRR0L = UBRR_Value;
	UBRR0H = (UBRR_Value >> 8);
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void uartTransmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

char uartReceive(void) {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

int main(void) {
	DDRB |= (1 << PORTB5);
	configUart();
	while (1) {
		char received = uartReceive();
		uartTransmit(received);
		PORTB ^= (1 << PORTB5);
	}
	return 0;
}
