.MODEL TINY
.186

CODESEG SEGMENT
    assume  CS:CODESEG, DS:CODESEG
    org     100h
main:
    jmp         init
    is_init     DW  1
    sys_hangler DD  0
    conf        DB  01Fh
    cur_sec     DB  0
    init_msg    DB  "Installed$", 13, 10
    exit_msg    DB  "Uninstalled$", 13, 10

what proc
    ; push used registers
    jmp CS:sys_hangler
    pushf
    push AX
    push CX
    push DX

    ; func
    mov AH, 02h
    int 1Ah

    cmp AH, cur_sec
    je to_pop

    mov AL, 0F3h
    out 60h, AL
    mov AL, conf
    out 60h, AL

    ; pop used registers
to_pop:
    pop DX
    pop CX
    pop AX
    iret
what endp

init:
    mov AX, 3509h
    int 21h

    cmp ES:is_init, 1
    je exit

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

exit:
    push DX
    push DS

    mov DX, word ptr ES:sys_hangler
    mov DS, word ptr ES:sys_hangler + 2

    mov AX, 2509h
    int 21h

    pop DS
    pop DX

    mov DX, offset exit_msg
    mov AH, 09h
    int 21h

    mov AH, 4Ch
    int 21h

CODESEG ENDS
END main