LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

Init:
; set 0X00 ~ 0X03 to 101112FF
    MOVLW 0x10
    MOVWF 0x00
    MOVLW 0x11
    MOVWF 0x01
    MOVLW 0x12
    MOVWF 0x02
    MOVLW 0xFF
    MOVWF 0x03
; set 0X10 ~ 0X13 to 202122FF
    MOVLW 0x20
    MOVWF 0x10
    MOVLW 0x21
    MOVWF 0x11
    MOVLW 0x22
    MOVWF 0x12
    MOVLW 0xFF
    MOVWF 0x13
; set FSR to be index
    LFSR 0, 0x03
    LFSR 1, 0x13
    LFSR 2, 0x23
; use 0x04 to be counter
Loop:
; count loop times
    BTFSC 0x04, 2
        GOTO Fin
    INCF 0x04
; calculate
    CALL Func
    GOTO Loop
Func:
; add FSR0 and FSR1
    MOVF INDF0, 0
    ADDWF INDF1, 0
    MOVWF INDF2
; move FSR to next address
    MOVF POSTDEC0, 1
    MOVF POSTDEC1, 1
    MOVF POSTDEC2, 1
; check if carry
    BNC 0x4C
        INCF INDF0
    RETURN
Fin:
    end