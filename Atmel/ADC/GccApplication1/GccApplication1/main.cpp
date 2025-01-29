/*
 * 10-bit ADC Visualization
 * Created: 29.01.2025
 * 
 * Description:
 * This program reads analog input from ADC channel 0 (PORTA0)
 * and displays the 10-bit result across PORTD (8 bits) and PORTB (2 bits)
 */

#include <avr/io.h>

void ADC_Init(void) {
    // Select Vref = AVcc
    ADMUX = (1<<REFS0);
    
    // Enable ADC, set prescaler to 128 (16MHz/128 = 125kHz)
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

uint16_t ADC_Read(uint8_t channel) {
    // Select ADC channel
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    
    // Start conversion
    ADCSRA |= (1<<ADSC);
    
    // Wait for conversion to complete
    while(ADCSRA & (1<<ADSC));
    
    // Return 10-bit result
    return ADC;
}

int main(void) {
    // Initialize ports as output
    DDRD = 0xFF;  // PORTD as output for lower 8 bits
    DDRB = 0x03;  // PORTB0 and PORTB1 as output for upper 2 bits
    
    // Initialize ADC
    ADC_Init();
    
    while(1) {
        // Read ADC value
        uint16_t adc_value = ADC_Read(0);
        
        // Output lower 8 bits to PORTD
        PORTD = adc_value & 0xFF;
        
        // Output upper 2 bits to PORTB
        PORTB = (adc_value >> 8) & 0x03;
    }
}