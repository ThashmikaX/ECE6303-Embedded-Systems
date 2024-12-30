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
    movlw       0x00                ; Turn off all 
    movwf       PORTA               
    btfsc       PORTA, 0            
    goto        on                  
    goto        start              

ledon:
    movlw       0x02                
    movwf       PORTA               
    goto        start               

    end                             