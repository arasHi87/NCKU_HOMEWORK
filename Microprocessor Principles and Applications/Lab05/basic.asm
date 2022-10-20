#include "xc.inc"
GLOBAL _isprime
    
PSECT mytext, local, class=CODE, reloc=2

_isprime:
; move input int to tmp
    MOVFF 0x01, 0x00
; set default answer
    MOVLW 0x01
    MOVWF 0x01
; init index to 2 on 0x11
    MOVLW 0x02
    MOVWF 0x11
Loop:
; return when index[0x11] >= input[0x00]
    MOVF 0x11, 0
    CPFSGT 0x00
        RETURN
    MOVFF 0x00, 0x10
    CALL Div
; if remainder[0x10] is 0 then set answer to 0xFF and return
    MOVLW 0x0
    SUBWF 0x10, 0
    BZ NotPrime
    INCF 0x11
    GOTO Loop
Div:
; return when divsor[0x11] > dividend[0x10]
    CLRF 0x12
    MOVF 0x11, 0
    CPFSGT 0x10
        INCF 0x12
    CPFSEQ 0x10
        INCF 0x12
    BTFSC 0x12, 1
        RETURN
    SUBWF 0x10, 1
    GOTO Div
NotPrime:
    MOVLW 0xFF
    MOVWF 0x01
    RETURN