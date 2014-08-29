
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char* xor(const void* in, const void* xor_key, size_t len, size_t *result_len) {
    unsigned char* data = (unsigned char*) in;
    unsigned char* key = (unsigned char*) xor_key;
    
    size_t count = 0;
    unsigned char* result = (unsigned char*) malloc(len);
    
    if(!result) {
        puts("Unable to allocate memory.");
        return 0;
    }
    
    unsigned char *pos = result;
    for(count = 0; count < len; count ++){
        *(pos++) = *(data + count) ^ *(key + count);
    }
    
    free(key);
    return result;    
}
