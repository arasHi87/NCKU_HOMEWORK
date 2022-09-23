LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

Init:
; set 0x10 to 0x0B
    MOVLW 0x0B
    MOVWF 0x10
; set 0x11 to 0x05
    MOVLW 0x05
    MOVWF 0x11
; set 0x12 to 0x40
    MOVLW 0x40
    MOVWF 0x12
; set 0x13 to 0x07
    MOVLW 0x07
    MOVWF 0x13
; set 0x14 to 0x0D
    MOVLW 0x0D
    MOVWF 0x14
; set 0x15 to 0x7F
    MOVLW 0x7F
    MOVWF 0x15
; set 0x16 to 0x0A
    MOVLW 0x0A
    MOVWF 0x16
; set 0x17 to 0x01
    MOVLW 0x01
    MOVWF 0x17
; set 0x18 to 0xFE
    MOVLW 0xFE
    MOVWF 0x18

; use 0x00 and 0x01 to be counter
; [0x00] => i
; [0x01] => j
; use FSR0 and FSR1 to be index
; [FSR0] => i
; [FSR0] => j
; do bubble sort algorithm
Loop1:
; clear Loop2 counter
    CLRF 0x00
; set Loop1&2 index
    LFSR 0, 0x10
    LFSR 1, 0x11
; run inside loop t0 compare FSR0 and FSR1
    CALL Loop2
; keep Loop1 running condition
; add 0x00 and end if it run 8 times
    INCF 0x00
    BTFSS 0x00, 3
        GOTO Loop1
    GOTO Fin

Loop2:
; compare FSR0 to FSR1, swap if FSR0 > FSR1
    MOVF INDF0, 0
    CPFSGT INDF1
        CALL Func
; move FSR to its next address
    MOVF POSTINC0, 1
    MOVF POSTINC1, 1
; keep Loop1 running condition
; add 0x01 and end if it run 8 times
    INCF 0x01
    BTFSS 0x01, 3
        GOTO Loop2
    RETURN

Func:
    MOVF INDF0
    MOVFF INDF1, INDF0
    MOVWF INDF1
    RETURN

Fin:
    end