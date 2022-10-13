LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

Init:
; set counter on 0x01
    MOVLW 0x02
    MOVWF 0x01
    CALL Hanoitower
    CALL Fin
Hanoitower:
; RETURN if n <= 0
    MOVLW 0x00
    CPFSGT 0x01
        RETURN
; [0x00] += 1
    INCF 0x00
    DECF 0x01
    CALL Hanoitower
    CALL Hanoitower
    INCF 0x01
    RETURN
Fin:
    end