#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define OK 0

#define BUFSIZE 100

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

int main(void)
{
    char test1_string[] = "";
    char test2_string[] = "Test string!!!";

    printf("Lenght tests\n");
    printf("TEST 1. Empty string\n");
    size_t stdlen = strlen(test1_string);
    size_t asmblen = asmlen(test1_string);
    printf("strlen = %ld\n", stdlen);
    printf("asmlen = %ld\n", asmblen);
    printf("%s", (stdlen == asmblen) ? "PASSED\n" : "FAILD\n");

    printf("TEST 2. General\n");
    stdlen = strlen(test2_string);
    asmblen = asmlen(test2_string);
    printf("strlen = %ld\n", stdlen);
    printf("asmlen = %ld\n", asmblen);
    printf("%s", (stdlen == asmblen) ? "PASSED\n" : "FAILD\n");

    return OK;
}