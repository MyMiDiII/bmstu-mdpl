EXTERN read_uoctal:near
EXTERN write_uhex:near
EXTERN write_sbin:near

STACKSEG SEGMENT PARA STACK 'STACK'
    DB 256 DUP(?)
STACKSEG ENDS

DATASEG SEGMENT PARA PUBLIC 'DATA'
    MENU_MSG DB  13, 10, "    MENU", 13, 10, 
                "1. ENTER UNSIGNED OCTAL NUMBER;", 13, 10, 
                "2. PRINT UNSIGNED HEX NUMBER;", 13, 10,
                "3. PRINT SIGNED BIN NUMBER;", 13, 10,
                "0. EXIT", 13, 10, 13, 10,
                "ENTER MENU NUMBER: $"
    func_ptr DW exit, read_uoctal, write_uhex, write_sbin
DATASEG ENDS

CODESEG SEGMENT PARA PUBLIC 'CODE'
    assume  CS: CODESEG, DS:DATASEG, SS:STACKSEG

main:
    mov AX, DATASEG
    mov DS, AX

    menu:
        ; print menu
        mov DX, offset MENU_MSG
        mov AH, 09
        int 21h

        ;read menu number
        mov AH, 01
        int 21h

        ;convert symb -> num
        mov AH, 0
        sub AX, "0"
        shl AX, 1
        mov BX, AX

        ;new line
        mov dl, 13
        mov AH, 02
        int 21h

        mov dl, 10
        mov AH, 02
        int 21h

        ;call func
        call func_ptr[BX]

    jmp main

exit PROC FAR
    mov AH, 4Ch
    int 21h
exit ENDP

CODESEG ENDS
END main