#include <stdio.h>
#include <string.h>

#define OK 0
#define RESET   "\033[0m"

#define PASSED "\033[1;32mPASSED\033[0m\n"
#define FAILED "\033[1;31mFAILED\033[0m\n"

#define BUFSIZE 20

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

    printf("\nLenght tests\n");
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

    char buffer[BUFSIZE] = "abcdrekjkjasdfkj";

    printf("\nCopy tests\n");
    printf("TEST 1. General\n");
    printf("SRC: %s\n", test2_string);
    printf("LEN: %lu\n", asmblen);
    asmstrcpy(buffer, test2_string, asmblen);
    printf("DST: %s\n", buffer);
    printf("%s", !strcmp(buffer, TEST_STRING) ? PASSED : FAILED);

    char buffer2[BUFSIZE] = "abcdrekjkjasdfkj";
    printf("TEST 2. String part\n");
    printf("SRC: %s\n", test2_string);
    printf("LEN: %lu\n", 4LU);
    asmstrcpy(buffer2, test2_string, 4);
    printf("OUT: %s\n", buffer2);
    printf("%s", !strcmp(buffer2, "Test") ? PASSED : FAILED);

    printf("TEST 3. DST = SRC\n");
    printf("SRC: %s\n", test2_string);
    printf("LEN: %lu\n", asmblen);
    asmstrcpy(test2_string, test2_string, asmblen);
    printf("OUT: %s\n", test2_string);
    printf("%s", !strcmp(test2_string, TEST_STRING) ? PASSED : FAILED);

    printf("TEST 4. DST < SRC (SRC - DST < len)\n");
    printf("SRC: %s\n", test2_string);
    printf("LEN: %lu\n", asmblen / 2);
    asmstrcpy(test2_string, test2_string + asmblen / 2, asmblen / 2);
    printf("OUT: %s\n", test2_string);
    printf("%s", !strcmp(test2_string, "ring!!!") ? PASSED : FAILED);

    char test2_copy[] = TEST_STRING;
    printf("TEST 5. DST > SRC (DST - SRC < len)\n");
    printf("SRC: %s\n", test2_copy);
    printf("LEN: %lu\n", asmblen);
    asmstrcpy(test2_copy + asmblen / 2, test2_copy, asmblen);
    printf("OUT: %s\n", test2_copy + asmblen / 2);
    printf("%s", !strcmp(test2_copy + asmblen / 2, TEST_STRING) ? PASSED : FAILED);

    char test2_copy2[] = TEST_STRING;
    printf("TEST 6. DST > SRC (DST - SRC == len)\n");
    printf("SRC: %s\n", test2_copy2);
    printf("LEN: %lu\n", asmblen);
    asmstrcpy(test2_copy2 + asmblen, test2_copy2, asmblen);
    printf("OUT: %s\n", test2_copy2 + asmblen);
    printf("%s", !strcmp(test2_copy2 + asmblen, TEST_STRING) ? PASSED : FAILED);

    return OK;
}