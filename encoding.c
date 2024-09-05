#include <string.h>
#include <stdio.h>

#include "encoding.h"


#define HEX "0123456789ABCDEF"


void mime_encode(char *buff, int buff_size)
{
    int i, j, len, c;

    for (i = 0; buff[i] != '\0' && i < buff_size; i++)
    {
        c = (unsigned char) buff[i];
        if (c < 32 || c >= 127)
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

void mime_decode(char *, int);
