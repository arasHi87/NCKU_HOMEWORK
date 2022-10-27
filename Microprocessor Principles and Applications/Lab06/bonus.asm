LIST p=18f4520
    #include<p18f4520.inc>
    CONFIG OSC = INTIO67
    CONFIG WDT = OFF
    CONFIG LVP = OFF
    
    L1      EQU 0x14
    L2      EQU 0x15
    org 0x00

DELAY macro num1, num2 
    local LOOP1 
    local LOOP2
    MOVLW num2
    MOVWF L2
LOOP2:
	MOVLW num1
	MOVWF L1
LOOP1:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	DECFSZ L1, 1
	BRA LOOP1
	DECFSZ L2, 1
	BRA LOOP2
endm

Init:
    MOVLW 0x0f
    MOVWF ADCON1
    CLRF LATA
    CLRF PORTB
    BSF TRISB, 0
    BCF TRISA, 0
    BCF TRISA, 1
    BCF TRISA, 2
    BCF TRISA, 3
Phase1:
    BTFSC PORTB, 0
    BRA Phase1
    BTG LATA, 0
    BTG LATA, 1
    CLRF LATA
    BTG LATA, 0
    BTG LATA, 1
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 1
    BTG LATA, 2
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 2
    BTG LATA, 3
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 3
    BTG LATA, 0
    DELAY d'200', d'30'
    CLRF LATA
    DELAY d'200', d'30'
Phase2:
    BTFSC PORTB, 0
    BRA Phase2
    BTG LATA, 0
    BTG LATA, 1
    CLRF LATA
    BTG LATA, 1
    BTG LATA, 2
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 2
    BTG LATA, 3
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 3
    BTG LATA, 0
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 0
    BTG LATA, 1
    DELAY d'200', d'30'
    CLRF LATA
    DELAY d'200', d'30'
Phase3:
    BTFSC PORTB, 0
    BRA Phase3
    BTG LATA, 0
    BTG LATA, 1
    CLRF LATA
    BTG LATA, 2
    BTG LATA, 3
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 3
    BTG LATA, 0
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 0
    BTG LATA, 1
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 1
    BTG LATA, 2
    DELAY d'200', d'30'
    CLRF LATA
    DELAY d'200', d'30'
Phase4:
    BTFSC PORTB, 0
    BRA Phase4
    BTG LATA, 0
    BTG LATA, 1
    CLRF LATA
    BTG LATA, 3
    BTG LATA, 0
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 0
    BTG LATA, 1
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 1
    BTG LATA, 2
    DELAY d'200', d'30'
    CLRF LATA
    BTG LATA, 2
    BTG LATA, 3
    DELAY d'200', d'30'
    CLRF LATA
    DELAY d'200', d'30'
    BRA Phase1
    end