#include "asmstr.h"

size_t asmlen(const char *const string)
{
    size_t len = 0;

    __asm__(
        ".intel_syntax noprefix\n"
        "mov rcx, -1\n"
        "mov rdi, %1\n"
        "mov al, 0\n"
        "repne scasb\n"
        "neg rcx\n"
        "sub rcx, 2\n"
        "mov %0, rcx\n"
        : "=r" (len)
        : "r" (string)
        : "rcx", "rdi", "al"
    );

    return len;
}