#include <stdio.h>
#include <string.h>

#include "tests.h"
#include "asmstr.h"

#define OK 0
#define BUFSIZE 20
#define TEST_STRING "Test string!!!"


int main(void)
{
    char test1_string[] = "";
    char test2_string[BUFSIZE] = TEST_STRING;

    printf("\nLenght tests\n");
    printf("TEST 1. Empty string\n");
    len_test(test1_string);

    printf("TEST 2. General\n");
    len_test(test2_string);

    size_t len = asmlen(test2_string);
    size_t half_len = len / 2;
    char buffer[BUFSIZE];
    strncpy(buffer, "abcdrekjkjasdfkj", BUFSIZE);

    printf("\nCopy tests\n");
    printf("TEST 1. General\n");
    strcpy_test(buffer, test2_string, len, TEST_STRING);

    strncpy(buffer, "abcdrekjkjasdfkj", BUFSIZE);
    printf("TEST 2. String part\n");
    strcpy_test(buffer, test2_string, 4, "Test");

    printf("TEST 3. DST = SRC\n");
    strcpy_test(test2_string, test2_string, len, TEST_STRING);

    strncpy(test2_string, TEST_STRING, BUFSIZE);
    printf("TEST 4. DST < SRC (SRC - DST < len)\n");
    strcpy_test(test2_string, test2_string + half_len,
                half_len, "ring!!!");

    strncpy(test2_string, TEST_STRING, BUFSIZE);
    printf("TEST 5. DST > SRC (DST - SRC < len)\n");
    strcpy_test(test2_string + half_len, test2_string, len, TEST_STRING);

    strncpy(test2_string, TEST_STRING, BUFSIZE);
    printf("TEST 6. DST > SRC (DST - SRC == len)\n");
    strcpy_test(test2_string + len, test2_string, len, TEST_STRING);

    return OK;
}