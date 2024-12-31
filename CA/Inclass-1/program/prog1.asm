    list        p=16f84a            ; Target microcontroller
    include     "P16F84A.INC"       ; Include PIC16F84A definitions

    __config    _XT_OSC & _WDT_OFF & _PWRTE_ON ; Configuration bits

    org         0x00                ; Program start address

; Initialize PORTA
    bsf         STATUS, RP0         ; Select Bank 1
    movlw       0x00                ; Set all pins of PORTA as output
    movwf       TRISA               ; Write to TRISA register
    bcf         STATUS, RP0         ; Select Bank 0

start:
    movlw       0x00                ; Turn off all pins of PORTA
    movwf       PORTA               ; Write 0 to PORTA
    btfsc       PORTA, 0            ; Check if bit 0 of PORTA is high
    goto        ledon               ; If high, jump to 'ledon'
    goto        start               ; Otherwise, loop back to 'start'

ledon:
    movlw       0x02                ; Set bit 1 of PORTA (turn on LED)
    movwf       PORTA               ; Write to PORTA
    goto        start               ; Return to main loop

    end                             ; End of program
