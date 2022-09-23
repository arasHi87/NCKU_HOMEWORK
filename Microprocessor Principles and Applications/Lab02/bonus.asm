LIST p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00

Init:
    MOVLB 1

    ; set 0x100 to 0xA1
    MOVLW 0xA1
    MOVWF 0x00, 1
    ; set 0x101 to 0xB2
    MOVLW 0xB2
    MOVWF 0x01, 1
    ; set 0x102 to 0xC3
    MOVLW 0xC3
    MOVWF 0x02, 1
    ; set 0x103 to 0xD4
    MOVLW 0xD4
    MOVWF 0x03, 1
    ; set 0x104 to 0xE5
    MOVLW 0xE5
    MOVWF 0x04, 1
    ; set 0x110 to 0xA7
    MOVLW 0xA7
    MOVWF 0x10, 1
    ; set 0x111 to 0xB3
    MOVLW 0xB3
    MOVWF 0x11, 1
    ; set 0x112 to 0xC9
    MOVLW 0xC9
    MOVWF 0x12, 1
    ; set 0x113 to 0xF6
    MOVLW 0xF6
    MOVWF 0x13, 1

; use FSR0 to be array1 index
; use FSR1 to be array2 index
; use FSR2 to be result index
    LFSR 0, 0x100
    LFSR 1, 0x110
    LFSR 2, 0x120

; use 0x05 to be i
; use 0x06 to be j
; while (i <= 5 && j <= 4)
WhileLoop:
; check if i <= 5
    MOVLW 0x05
    CPFSLT 0x05, 1
        GOTO WhileEnd
; check if j <= 4
    BTFSC 0x06, 2, 1
        GOTO WhileEnd
; if (arr[i] < arr[j]) result[idx++] = arr[i]
    MOVF INDF0, 0
    CPFSLT INDF1
        GOTO MoveI
; else
    GOTO MoveJ

MoveI:
    MOVFF POSTINC0, POSTINC2
    INCF 0x05, 1, 1
    GOTO WhileLoop

MoveJ:
    MOVFF POSTINC1, POSTINC2
    INCF 0x06, 1, 1
    GOTO WhileLoop

WhileEnd:

WhileILoop:
; check if i <= 5
    MOVLW 0x05
    CPFSLT 0x05, 1
        GOTO WhileIEnd
    MOVFF POSTINC0, POSTINC2
    INCF 0x05, 1, 1
    GOTO WhileILoop

WhileIEnd:

WhileJLoop:
; check if j <= 5
    BTFSC 0x06, 2, 1
        GOTO Fin
    MOVFF POSTINC1, POSTINC2
    INCF 0x06, 1, 1
    GOTO WhileJLoop
Fin:
    end