EXTERN num:word

PUBLIC write_sbin

DATASEG SEGMENT PARA PUBLIC 'DATA'
    bin_num DB 18 DUP("$")
    BIN_MASK DW 1
    OUTPUTSBIN_MSG DB 13, 10, "THE SIGNED BIN NUMBER IS $"
DATASEG ENDS

CODESEG SEGMENT PARA PUBLIC 'CODE'
    assume  CS:CODESEG, DS:DATASEG

write_sbin PROC NEAR
    mov BX, 0
    mov bin_num[BX], " "

    mov AX, num
    cmp AX, 32767
    jbe nonneg

    ; add "-"
    neg AX
    mov bin_num[BX], "-"

    nonneg:
    mov CX, 16

    tosbin:
        ;find bin digit
        mov BX, AX
        and BX, BIN_MASK

        ; add to string
        add BX, "0"
        mov SI, CX
        mov bin_num[SI], BL
        mov CX, 1
        shr AX, CL
        mov CX, SI
    loop tosbin

    ; print result
    mov AH, 09h
    mov DX, offset OUTPUTSBIN_MSG
    int 21h

    mov DX, offset bin_num
    int 21h

    ;new line
    mov dl, 13
    mov AH, 02
    int 21h

    mov dl, 10
    mov AH, 02
    int 21h

    ret
write_sbin ENDP


CODESEG ENDS
END