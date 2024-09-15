#include <string.h>

#include "encoding.h"


#define HEX "0123456789ABCDEF"


void mime_encode(char *buff, int buff_size)
{
    int i, j, c;

    for (i = 0; buff[i] != '\0' && i < buff_size; i++)
    {
        c = (unsigned char) buff[i];
        if (c < 32 || c >= 127 || c == '=')
        {
            for (j = strlen(buff); j > i; j--)
            {
                buff[j + 2] = buff[j];
            }

            buff[i]     = '=';
            buff[i + 1] = HEX[(c & 0xf0) >> 4];
            buff[i + 2] = HEX[ c & 0x0f];
            i = i + 2;
        }

    }
}

int hex_to_int(char h)
{
    int i;
    if (h >= 'a' && h <= 'f')
    {
        h = h & 0b1011111;
    }

    for (i = 0; i < 16; i++)
    {
        if (h == HEX[i])
            return i;
    }

    return -1;
}

void mime_decode(char *buff, int buff_size)
{
    int i, j;
    char c;

    for (i = 0; buff[i] != '\0' && i < buff_size; i++)
    {
        if (buff[i] == '=' && buff[i + 1] != '?')
        {
            c = (hex_to_int(buff[i + 1]) << 4) + hex_to_int(buff[i + 2]);

            for (j = i; j < strlen(buff); j++)
            {
                buff[j] = buff[j + 2];
            }

            buff[i] = c;
        }
    }
}
