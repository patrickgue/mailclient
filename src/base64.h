#ifndef base64_h
#define base64_h

#include <stdlib.h>

int base64_encode(char *base64_buff, size_t base64_buff_size, char *source, size_t source_size);
int base64_decode(char *output_buff, size_t output_buff_size, char *base64_source, size_t base64_source_size);
#endif
