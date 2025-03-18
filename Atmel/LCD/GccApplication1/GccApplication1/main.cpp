#define F_CPU 16000000UL  // Define CPU frequency for delays
#include <avr/io.h>
#include <util/delay.h>

// Define LCD control pins
#define RS PD6
#define RW PD5
#define EN PD4

// Define LCD data pins
#define D4 PD3
#define D5 PD2
#define D6 PD1
#define D7 PD0

// Function prototypes
void LCD_Command(unsigned char cmd);
void LCD_String(const char *str);  // Use const char*
void LCD_Init();
void LCD_String(char *str);
void LCD_Clear();

int main(void) {
	// Configure LCD pins as output
	DDRD |= (1 << RS) | (1 << RW) | (1 << EN) | (1 << D4) | (1 << D5) | (1 << D6) | (1 << D7);
	
	LCD_Init();  // Initialize LCD

	LCD_String("DEIE");  // Display "DEIE"
	_delay_ms(1000);  // Wait for 1 second

	LCD_Clear();  // Clear the LCD

	while (1) {
		// Main loop (empty)
	}
}

// Send command to LCD
void LCD_Command(unsigned char cmd) {
	PORTD = (PORTD & 0x0F) | (cmd & 0xF0);  // Send upper nibble
	PORTD &= ~(1 << RS);  // RS = 0 for command
	PORTD &= ~(1 << RW);  // RW = 0 for write
	PORTD |= (1 << EN);   // Enable pulse
	_delay_us(1);
	PORTD &= ~(1 << EN);

	_delay_us(200);

	PORTD = (PORTD & 0x0F) | (cmd << 4);  // Send lower nibble
	PORTD |= (1 << EN);
	_delay_us(1);
	PORTD &= ~(1 << EN);

	_delay_ms(2);  // Command execution time
}

// Send a character to the LCD
void LCD_Char(unsigned char data) {
	PORTD = (PORTD & 0x0F) | (data & 0xF0);  // Send upper nibble
	PORTD |= (1 << RS);  // RS = 1 for data
	PORTD &= ~(1 << RW);  // RW = 0 for write
	PORTD |= (1 << EN);
	_delay_us(1);
	PORTD &= ~(1 << EN);

	_delay_us(200);

	PORTD = (PORTD & 0x0F) | (data << 4);  // Send lower nibble
	PORTD |= (1 << EN);
	_delay_us(1);
	PORTD &= ~(1 << EN);

	_delay_ms(2);
}

// Initialize LCD
void LCD_Init() {
	_delay_ms(20);  // Wait for LCD to power up

	LCD_Command(0x02);  // Initialize LCD in 4-bit mode
	LCD_Command(0x28);  // 2 lines, 5x8 matrix
	LCD_Command(0x0C);  // Display ON, Cursor OFF
	LCD_Command(0x06);  // Entry mode
	LCD_Command(0x01);  // Clear display
	_delay_ms(2);
}

void LCD_String(const char *str) {
	while (*str) {
		LCD_Char(*str++);
	}
}

// Clear LCD screen
void LCD_Clear() {
	LCD_Command(0x01);
	_delay_ms(2);
}
