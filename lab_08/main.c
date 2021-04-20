#include <stdio.h>
#include <string.h>

#define OK 0
#define RESET   "\033[0m"

#define PASSED "\033[1;32mPASSED\033[0m\n"
#define FAILED "\033[1;31mFAILED\033[0m\n"

#define BUFSIZE 100

#define TEST_STRING "Test string!!!"

void asmstrcpy(char *dst, const char *src, const size_t len);

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
    char test2_string[] = TEST_STRING;

    printf("Lenght tests\n");
    printf("TEST 1. Empty string\n");
    size_t stdlen = strlen(test1_string);
    size_t asmblen = asmlen(test1_string);
    printf("strlen = %ld\n", stdlen);
    printf("asmlen = %ld\n", asmblen);
    printf("%s", (stdlen == asmblen) ? PASSED : FAILED);

    printf("TEST 2. General\n");
    stdlen = strlen(test2_string);
    asmblen = asmlen(test2_string);
    printf("strlen = %ld\n", stdlen);
    printf("asmlen = %ld\n", asmblen);
    printf("%s", (stdlen == asmblen) ? PASSED : FAILED);

    char buffer[BUFSIZE];

    printf("Copy tests\n");
    printf("TEST 1. General\n");
    printf("IN : %s\n", test2_string);
    asmstrcpy(buffer, test2_string, asmblen);
    printf("OUT: %s\n", test2_string);
    printf("%s", strcmp(buffer, TEST_STRING) ? PASSED : FAILED);

    printf("TEST 2. String part\n");
    printf("IN : %s\n", test2_string);
    asmstrcpy(buffer, test2_string, 4);
    printf("OUT: %s\n", test2_string);
    printf("%s", strcmp(buffer, TEST_STRING) ? PASSED : FAILED);

    printf("TEST 3. DST = SRC\n");
    printf("IN : %s\n", test2_string);
    asmstrcpy(test2_string, test2_string, asmblen);
    printf("OUT: %s\n", test2_string);
    printf("%s", strcmp(buffer, TEST_STRING) ? PASSED : FAILED);

    printf("TEST 4. DST < SRC (SRC - DSC < len)\n");
    printf("IN : %s\n", test2_string);
    asmstrcpy(test2_string, test2_string + asmblen / 2, asmblen);
    printf("OUT: %s\n", test2_string);
    printf("%s", strcmp(buffer, TEST_STRING) ? PASSED : FAILED);

    printf("TEST 5. DST > SRC (DSC - SRC < len)\n");
    printf("IN : %s\n", test2_string);
    asmstrcpy(test2_string + asmblen / 2, test2_string, asmblen);
    printf("OUT: %s\n", test2_string);
    printf("%s", strcmp(buffer, TEST_STRING) ? PASSED : FAILED);

    printf("TEST 6. DST > SRC (DSC - SRC == len)\n");
    printf("IN : %s\n", test2_string);
    asmstrcpy(test2_string + asmblen, test2_string, asmblen);
    printf("OUT: %s\n", test2_string);
    printf("%s", strcmp(TEST_STRING, buffer) ? PASSED : FAILED);

    return OK;
}