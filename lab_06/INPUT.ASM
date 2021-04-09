PUBLIC read_uoctal
PUBLIC num

DATASEG SEGMENT PARA PUBLIC 'DATA'
    num DW 0 
    BASE DW 8
    INPUT_MSG DB 13, 10, "ENTER UNSIGNED OCTAL NUMBER (0 to 177777): $"
DATASEG ENDS

CODESEG SEGMENT PARA PUBLIC 'CODE'
    assume  CS:CODESEG, DS:DATASEG

read_uoctal PROC NEAR
    ; print msg
    mov num, 0
    mov AX, DATASEG
    mov DS, AX

    mov DX, offset INPUT_MSG
    mov AH, 09
    int 21h
    
    mov AH, 01h
    mov CX, 0

    read:
        ; read symb
        int 21h
        cmp AL, 13
        JE ok

        ; add new digit to number
        sub AL, "0"
        mov CL, AL
        mov AX, num
        mul BASE
        add AX, CX
        mov num, AX

        mov AH, 01h
    jmp read

    ok: ret
read_uoctal ENDP

CODESEG ENDS
END