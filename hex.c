
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "crypt_error.h"

crypt_error check_valid_hex(const unsigned char* hex) {
    if(sizeof(hex) == 0) {
        return input_empty;
    }
    
    if(hex[0] == '\0') {
        return input_empty;
    }
    
    if(strlen(hex) % 2 != 0)
    { 
        return input_not_even;
    }
    
    return none;
}

crypt_error hex_to_bytes(unsigned char* hex, unsigned char * result, size_t bufsize) {
    
    crypt_error err = check_valid_hex(hex);
    
    if(err != none) {
        result = "";
        return err;
    }
     
    if(bufsize < strlen(hex) - 1) {        
        result = "";
        return result_buffer_too_small;
    }
    
    unsigned char *pos = hex;    
    size_t count = 0;
    
    for(;count < sizeof(result); count++) {
        // Scan 2 bytes as hex
        sscanf(pos, "%2hhx", &result[count]);
        // Advance in the hex string
        pos += 2 * sizeof(char);
    }

    return none;
}
