EXTERN num:word

PUBLIC write_uhex

DATASEG SEGMENT PARA PUBLIC 'DATA'
    hex_num DB 5 DUP("$")
    HEX_MASK DW 15
    OUTPUTUHEX_MSG DB 13, 10, "THE UNSIGNED HEX NUMBER IS $"
DATASEG ENDS

CODESEG SEGMENT PARA PUBLIC 'CODE'
    assume  CS:CODESEG, DS:DATASEG

write_uhex PROC NEAR
    mov AX, num

    mov CX, 4

    touhex:
        ; find hex digit
        mov BX, AX
        and BX, HEX_MASK

        cmp BX, 0Ah

        jb digit

        ; is letter
        sub BX, 0Ah
        add BX, "A"

        jmp common

        ; is digit
        digit:
            add BX, "0"
    
        ; add to string
        common:
            mov SI, CX
            mov hex_num[SI - 1], BL
            mov CX, 4
            shr AX, CL
            mov CX, SI


    loop touhex

    ; print result
    mov AH, 09h
    mov DX, offset OUTPUTUHEX_MSG
    int 21h

    mov DX, offset hex_num
    int 21h

    ;new line
    mov dl, 13
    mov AH, 02
    int 21h

    mov dl, 10
    mov AH, 02
    int 21h

    ret
write_uhex ENDP


CODESEG ENDS
END