#include "xc.inc"
GLOBAL _divide_signed
    
PSECT mytext, local, class=CODE, reloc=2

_divide_signed:
; move dividend[WREG] to [0x10]
; also move to [0x14], will use in check
    MOVWF 0x10
    MOVWF 0x14
; move divisor[0x01] to [0x11]
    MOVFF 0x01, 0x11
    MOVFF 0x01, 0x15
; take absolute value
    MOVF 0x10, 0
    CALL Abso
    MOVWF 0x10
    MOVF 0x11, 0
    CALL Abso
    MOVWF 0x11
; division
    CLRF 0x12
Div:
    CLRF 0x13
    MOVF 0x11, 0
    CPFSGT 0x10
        INCF 0x13
    CPFSEQ 0x10
        INCF 0x13
    BTFSC 0x13, 1
        GOTO Check
    SUBWF 0x10, 1
    INCF 0x12
    GOTO Div
Check:
; If the divisor and the divisor are different signed, the quotient is negative
; if (a ^ b) < 0
    MOVF 0x14, 0
    XORWF 0x15, 0
    BTFSC WREG, 7
        CALL Negative
; check remainder
    BTFSC 0x14, 7
        CALL Negative_1
; move quotient and remainder to 0x01
; quotient in high 4 bits
; remainder in low 4 bits
    MOVFF 0x12, 0x02
    MOVFF 0x10, 0x01
    RETURN
Abso:
    BTFSS WREG, 7
        RETURN
    COMF WREG, 0
    INCF WREG
    RETURN
Negative:
    COMF 0x12, 1
    INCF 0x12
    RETURN
Negative_1:
    COMF 0x10, 1
    INCF 0x10
    RETURN