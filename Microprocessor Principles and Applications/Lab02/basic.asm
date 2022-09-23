LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

Init:
; move 0x01 to 0x10 and 0x11
    MOVLW 0x01
    MOVWF 0x10
    MOVWF 0x11

; move timer to 0x19
    MOVLW 0x08
    MOVWF 0x19

; set SFR 0, 1, 2
    LFSR 0, 0x10
    LFSR 1, 0x11
    LFSR 2, 0x12

Loop:
    DCFSNZ 0x19, 1
        GOTO Fin
    CALL Func
    GOTO Loop

Func:
    ; move SFR0 to WREG, SFR0 += 1
    ; move SFR1 to SFR2, SFR1 += 1
    ; [SFR2 += WREF], SFR2 += 1
    MOVF POSTINC0, 0
    MOVFF POSTINC1, INDF2
    ADDWF POSTINC2, 1
    RETURN
Fin:
    end