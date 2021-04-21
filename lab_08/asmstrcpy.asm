global asmstrcpy
section .text

asmstrcpy:
    mov rcx, rdx
    mov rbx, rdi

    cmp rdi, rsi
    jbe copy    ; DTS <= SRC

    mov rax, rdi
    sub rax, rsi

    cmp rax, rcx
    ja copy     ; DST - SRC < len

    add rdi, rcx
    add rsi, rcx
    dec rsi
    dec rdi
    std

copy:
    rep movsb
    cld

    mov byte [rbx + rdx], 0
quit:
    ret
