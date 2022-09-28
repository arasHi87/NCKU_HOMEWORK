LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

Init:
; set 0x11 to 0x06
    MOVLW b'01100000'
    MOVWF 0x11
; set 0x01 to 0x17
    MOVLW b'00010111'
    MOVWF 0x01
; call 4 times ALU
    CALL Func
    CALL Func
    CALL Func
    CALL Func
    CALL Func
    CALL Fin
; div ALU
Func:
; check divisor and dividend which is larger
    MOVF 0x11, 0
    SUBWF 0x01, 0
    BNN Tag
        CALL Smaller
        RRNCF 0x11, 1
        RETURN
Tag:
    CALL Larger
    RRNCF 0x11, 1
    RETURN
; divisor larger then dividend
Larger:
    MOVF 0x11, 0
    SUBWF 0x01, 1
    RLNCF 0x00, 1
    BSF 0x00, 0
    RETURN
; divisor smaller then dividend
Smaller:
    RLNCF 0x00, 1
    BCF 0x00, 0
    RETURN
Fin:
    end