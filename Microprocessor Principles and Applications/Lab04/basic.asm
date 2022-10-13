LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

CAL MACRO x, y, F1, F2
    MOVLW y
    SUBLW x
    MULWF WREG
    MOVFF PRODH, F1
    MOVFF PRODL, F2
    endm

DIST MACRO x1, y1, x2, y2, F1, F2
; (x1 - x2)^2, store in [0x10, 0x11]
    CAL x1, x2, 0x10, 0x11
; (y1 - y2)^2, store in [0x20, 0x21]
    CAL y1, y2, 0x20, 0x21
; F1 + F2 (low)
    MOVFF 0x11, WREG
    MOVFF 0x21, F2
    ADDWF F2, 1
; F1 + F2 (high)
    MOVFF 0x10, WREG
    MOVFF 0x20, F1
    ADDWFC F1, 1
    endm

Init:
    DIST 0x05, 0x07, 0x02, 0x03, 0x00, 0x01
Fin:
    end