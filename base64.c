#include "base64.h"

#include <stdio.h>

#define ALPH "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

int base64_encode(char *base64_buff, size_t base64_buff_size, char *source, size_t source_size)
{
    int i, bit, b64_i = 0, end_index;
    unsigned char buff = 0;
    /* iterate through all bits */
    for (i = 0; i < source_size * 8; i++)
    {
        bit = source[i / 8] & (0b10000000 >> (i % 8)) ? 0b100000 : 0;
        buff = buff | (bit >> (i % 6));

        if ((i + 1) % 6 == 0)
        {

            base64_buff[b64_i++] = ALPH[buff];
            buff = 0;
        }
    }
    if (i % 6 != 0)
    {
        base64_buff[b64_i++] = ALPH[buff];
        buff = 0;
    }

    for (i = 0; i < (3 - (source_size % 3)) % 3; i++)
    {
        base64_buff[b64_i++] = '=';
        buff = 0;
    }
    return 0;
}


int base64_decode(char *output_buff, size_t output_buff_size, char *base64_source, size_t base64_source_size)
{
    int i, j, curr_alph_index, bit;
    unsigned char curr_byte = 0;

    for (i = 0; i < base64_source_size * 6; i++)
    {
        if (i % 6 == 0)
        {
            if (base64_source[i / 6] == '=')
                goto end;
            for (j = 0; j < 64; j++)
            {
                if (base64_source[i / 6] == ALPH[j])
                {
                    curr_alph_index = j;
                    break;
                }
            }
        }

        bit = (curr_alph_index & (0b100000 >> (i % 6))) ? (0b10000000 >> (i % 8)) : 0;
        curr_byte = curr_byte | bit;

        if ((i + 1) % 8 == 0)
        {
            output_buff[i / 8] = curr_byte;
            curr_byte = 0;
        }
    }
end:

    if (i % 8 != 0)
    {
        output_buff[i / 8] = curr_byte;
    }

    return i / 8;
}
