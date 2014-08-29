
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool check_valid_hex(const unsigned char* hex) {
    if(sizeof(hex) == 0) {
        return false;
    }
    
    if(hex[0] == '\0') {
        return false;
    }
    
    if(strlen(hex) % 2 != 0)
    { 
        return false;
    }
    
    return true;
}

unsigned char* hex_to_bytes(unsigned char* hex, size_t len, size_t *result_len) {
    
    bool isValid = check_valid_hex(hex);
    
    if(!isValid) {        
        *result_len = 0;
        return 0;
    }
    
    unsigned char *result = (unsigned char*) malloc(len);
    
    if(!result) {
        puts("Cannot allocate memory.");
        return 0;
    }
    
    unsigned char *pos = hex;    
    size_t count = 0;
    
    for(;count < len; count++) {
        // Scan 2 bytes as hex
        sscanf(pos, "%2hhx", &result[count]);
        // Advance in the hex string
        pos += 2 * sizeof(char);
    }
    
    *result_len = count;
    return result;
}

unsigned char *bytes_to_hex(const void* bytes, size_t len, size_t *result_len) {    
    unsigned char *input = (unsigned char *) bytes;
    
    size_t out_len = len * 2 + 1;
    unsigned char *result = (unsigned char*) malloc(out_len);
    
    if(!result) {
        puts("Cannot allocate memory.");
        return 0;
    }
    
    unsigned char* pos = result;
    size_t count = 0;    
    for(count = 0; count < out_len; count++) {
        pos += sprintf(pos, "%02x", input[count]);       
    }
    
    *result_len = out_len;
    *(result + out_len - 1) = '\0';
    return result;
}