LIST    P=16F84A
    INCLUDE P16F84A.INC
    
    __CONFIG _CP_OFF & _WDT_OFF & _PWRTE_ON & _XT_OSC
    COUNTER EQU 0x20
    
    ORG     0x00
    goto    START
    
    ORG     0x04
    retfie
    
START
    bsf     STATUS, RP0    ; Bank 1
    movlw   b'00000000'    ; Set PORTA as output
    movwf   TRISA
    bcf     STATUS, RP0    ; Bank 0
    
    clrf    PORTA
    clrf    COUNTER
    
MAIN_LOOP
    movf    COUNTER, W     ; Get counter value
    movwf   PORTA         ; Send directly to PORTA (no inversion needed for 74LS47)
    call    DELAY
    
    incf    COUNTER, F    ; Increment counter
    movlw   .10          ; Check if counter reached 10
    subwf   COUNTER, W
    btfss   STATUS, Z
    goto    MAIN_LOOP
    
    clrf    COUNTER      ; Reset counter to 0
    goto    MAIN_LOOP
    
DELAY
    movlw   .255
    movwf   0x21
DELAY_LOOP1
    movlw   .255
    movwf   0x22
DELAY_LOOP2
    decfsz  0x22, F
    goto    DELAY_LOOP2
    decfsz  0x21, F
    goto    DELAY_LOOP1
    return
    
    END