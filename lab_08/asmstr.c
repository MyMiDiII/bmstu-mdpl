#include "asmstr.h"

size_t asmlen(const char *const string)
{
    size_t len = 0;

    __asm__(
        ".intel_syntax noprefix\n"
        "mov rcx, 0xffffffffffffffff\n"
        "mov rdi, %1\n"
        "mov al, 0\n"
        "repne scasb\n"
        "mov rax, 0xffffffffffffffff\n"
        "sub rax, rcx\n"
        "dec rax\n"
        "mov %0, rax\n"
        : "=r" (len)
        : "r" (string)
        : "ecx", "rdi", "al", "eax"
    );

    return len;
}