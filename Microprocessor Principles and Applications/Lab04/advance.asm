LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

Init:
; [0x00] = 0x01
    MOVLW 0x01
    MOVWF 0x00
; [0x01] = 0x03
    MOVLW 0x03
    MOVWF 0x01
; move first number to result
    MOVFF 0x00, 0x02
    RCALL GP
    RCALL GP
; change PCL to end
    MOVLW 0x26
    MOVWF PCL
GP:
    MOVF 0x01, 0
    MULWF 0x00
    MOVFF PRODL, 0x00
    MOVF PRODL, 0
    ADDWF 0x02
    RETURN
Fin:
    end