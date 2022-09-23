LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

INIT:
; store 0x17 in 0x00
    MOVLW 0x17
    MOVWF 0x00

; store loop times in 0x01
    MOVLW 0x08
    MOVWF 0x01

LOOP:
    ; check loop times
    DCFSNZ 0x01, 1
        GOTO FINISH
    
    ; rorate 0x00 and compare to WREG
    MOVLW 0x01
    ANDWF 0x00, 0
    TSTFSZ WREG
        INCF 0x02
    RRNCF 0x00, 1
    GOTO LOOP
FINISH:
    end