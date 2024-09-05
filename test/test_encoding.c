#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../encoding.h"

void succ(char *msg)
{
    printf("%-30s[SUCCESS]\n", msg);
}

void dbg(char *str)
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        printf("%02x ", i);
    }

    printf("\n");
    for (i = 0; i < strlen(str); i++)
    {
        printf("%02x ", (unsigned char)str[i]);
    }
    printf("\n");

    for (i = 0; i < strlen(str); i++)
    {
        if (((unsigned char)str[i]) < 127)
            printf("%2c ",str[i]);
        else
            printf(" _ ");
    }
    printf("\n");
}

void test_encoding()
{
    /* UTF-8 encoded string  */
    char buff[64] = {'S', 'a', 'l', 0xC3, 0xBC, ' ', 'W', 'o', 'r', 'l', 'd', 0};
    mime_encode(buff, 64);
    assert(strcmp(buff, "Sal=C3=BC World") == 0);
}

int main(void)
{
    test_encoding(); succ("mime_encode");
}
