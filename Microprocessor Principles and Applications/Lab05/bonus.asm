#include "xc.inc"
GLOBAL _mypow
    
PSECT mytext, local, class=CODE, reloc=2

_mypow:
; move base[0x01] to 0x10
; move power[0x03] to 0x11
    MOVFF 0x01, 0x10
    MOVFF 0x03, 0x11
; init answer, set [0x01] to 0x01
    MOVLW 0x01
    MOVWF 0x01
    INCF 0x11
; run until power to zero
Loop:
    DCFSNZ 0x11
        RETURN
    MOVF 0x10, 0
; multiply low byte
    MULWF 0x01
    MOVFF PRODL, 0x01
    MOVFF PRODH, 0x13
; multiply high byte
    MULWF 0x02
    MOVFF PRODL, 0x02
    MOVF 0x13, 0
    ADDWF 0x02, 1
    GOTO Loop