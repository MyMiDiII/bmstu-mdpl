global asmstrcpy
section .text

asmstrcpy:
    mov rcx, rdx

    cmp rdi, rsi
    je quit
    jl copy

    mov rax, rdi
    sub rax, rsi

    cmp rax, rcx
    jge copy

    add rdi, rcx
    add rsi, rcx
    dec rsi
    dec rdi
    std

copy:
    rep movsb
    cld
quit:
    ret
