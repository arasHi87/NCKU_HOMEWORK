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
    BRA LightUp1
Phase2:
    BTFSC PORTB, 0
    BRA Phase2
    BRA LightUp2
Phase3:
    BTFSC PORTB, 0
    BRA Phase3
    BRA LightUp3
Phase4:
    BTFSC PORTB, 0
    BRA Phase4
    BRA LightUp4
Phase5:
    BTFSC PORTB, 0
    BRA Phase5
    BRA LightUp5
LightUp1:
    BTG LATA, 0
    DELAY d'200', d'20'
    BRA Phase2
LightUp2:
    BTG LATA, 1
    DELAY d'200', d'20'
    BRA Phase3
LightUp3:
    BTG LATA, 2
    DELAY d'200', d'20'
    BRA Phase4
LightUp4:
    BTG LATA, 3
    DELAY d'200', d'20'
    BRA Phase5
LightUp5:
    CLRF LATA
    DELAY d'200', d'20'
    BRA Phase1
end