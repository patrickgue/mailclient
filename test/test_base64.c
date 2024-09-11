#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "test.h"

#include "../base64.h"

void test_encode()
{
    char str[] = "Hello";
    char exp[] = "SGVsbG8=";
    char buff[32];

    base64_encode(buff, sizeof buff, str, strlen(str));
    assert(strcmp(buff, exp) == 0);    
}

void test_decode()
{
    char str[] = "SGVsbG8=";
    char exp[] = "Hello";
    char buff[32];

    base64_decode(buff, sizeof buff, str, strlen(str));
    assert(strcmp(buff, exp) == 0);

}

void test_run_base64()
{
    test_encode(); succ("base64 encode");
    test_decode(); succ("base64 decode");
}
