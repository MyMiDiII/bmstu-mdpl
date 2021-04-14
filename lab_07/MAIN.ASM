.MODEL TINY

CODESEG SEGMENT
    assume  CS:CODESEG, DS:CODESEG
    org     100h
main:
    jmp         init
    sys_hangler DD  0
    init_msg    DB  "Installed$", 13, 10

what proc
    pushf
    call CS:sys_hangler
    ; push used registers

    ; func

    ; pop used registers
    iret
what endp


init:
    mov AX, 3509h
    int 21h

    mov word ptr sys_hangler, BX
    mov word ptr sys_hangler + 2, ES 

    mov AX, 2509h
    mov DX, offset what
    int 21h

    mov DX, offset init_msg
    mov AH, 09h
    int 21h

    mov DX, offset init
    int 27h

CODESEG ENDS
END main