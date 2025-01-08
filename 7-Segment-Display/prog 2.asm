LIST P=16F84A
    #include <P16F84A.INC>
    
    ; Configuration bits
    __CONFIG _CP_OFF & _WDT_OFF & _PWRTE_ON & _XT_OSC
    
    ; Variable definitions
    COUNTER    EQU    0x0C        ; Counter variable
    DELAY_1    EQU    0x0D        ; Delay variable 1
    DELAY_2    EQU    0x0E        ; Delay variable 2
    
    ; Reset vector
    ORG     0x000
    GOTO    START
    
    ; Main program
    ORG     0x005
START
    BSF     STATUS, RP0      ; Select Bank 1
    CLRF    TRISB           ; Set PORTB as output
    BCF     STATUS, RP0      ; Select Bank 0
    
MAIN_LOOP
    CLRF    COUNTER         ; Initialize counter to 0
    
DISPLAY_LOOP
    MOVF    COUNTER, W      ; Move counter value to W
    ANDLW   0x0F            ; Mask upper nibble
    MOVWF   PORTB           ; Output to PORTB (connected to 74LS47)
    CALL    DELAY           ; Wait before showing next number
    INCF    COUNTER, F      ; Increment counter
    MOVLW   0x0A            ; Load 10 into W
    SUBWF   COUNTER, W      ; Check if counter = 10
    BTFSS   STATUS, Z       ; Skip if counter = 10
    GOTO    DISPLAY_LOOP    ; If counter < 10, continue display loop
    GOTO    MAIN_LOOP       ; If counter = 10, reset to 0
    
; Delay subroutine
DELAY
    MOVLW   0xFF
    MOVWF   DELAY_1
DELAY_LOOP1
    MOVLW   0xFF
    MOVWF   DELAY_2
DELAY_LOOP2
    DECFSZ  DELAY_2, F
    GOTO    DELAY_LOOP2
    DECFSZ  DELAY_1, F
    GOTO    DELAY_LOOP1
    RETURN

    END                     ; End of program