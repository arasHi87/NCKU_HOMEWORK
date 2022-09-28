LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

Init:
	MOVLW 0xF5
	MOVWF 0x010
	MOVWF 0x020
	MOVLW 0x5A
	MOVWF 0x011
	MOVWF 0x021
; Get GCD for 0xF5 and 0x5A
	CALL Gcd
; Div GCD
	MOVFF 0x010, 0x020
	CALL Div
; Mul 0x030 and 0x011
	MOVF 0x030, 0
	MULWF 0x011
; move result to 0x00 and 0x01
	MOVFF PRODH, 0x00
	MOVFF PRODL, 0x01
	GOTO Fin
; =========================
; = GCD Implement         =
; =========================
Gcd:
; check if 0x020 is smaller then 0x021
; if so then swap them
	MOVF 0x020, 0
	CPFSLT 0x021
		CALL Swap
; 0x020 - 0x021
	MOVF 0x021, 0
	SUBWF 0x020, 1
	BZ Gcd_End
		GOTO Gcd
Swap:
	MOVF 0x020, 0
	MOVFF 0x021, 0x020
	MOVFF WREG, 0x021
	RETURN
Gcd_End:
	RETURN
; =========================
; = Divider Implement     =
; =========================
Div:
; 0x020 - 0x021
	MOVF 0x021, 0
	SUBWF 0x020, 1
	BZ Div_end
		INCF 0x030
		GOTO Div
Div_end:
	INCF 0x030
	RETURN
Fin:
	end