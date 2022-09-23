LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

init:
; set 0x00 to 0x7c
    MOVLW 0x7C
    MOVWF 0x00

; set 0x01 to 0x04
    MOVLW 0x04
    MOVWF 0x01
    
; do 2's complement on 0x00
    COMF 0x00, 1
    INCF 0x00, 1

; compare 0x00 and 0x01
    MOVF 0x00, 0
    CPFSEQ 0x01
    GOTO neq
eq:
    MOVLW 0xFF
    MOVWF 0x02
    GOTO fin
neq:
    MOVLW 0x01
    MOVWF 0x02
fin:
end