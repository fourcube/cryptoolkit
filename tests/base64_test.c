#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../lib/tap.h"


unsigned char *test_encode_base64() {
    unsigned char input[1] = {'\x00'};
    size_t len = 1;
    size_t result_length;
        
    unsigned char *result = encode_base64(input, len, &result_length);
        
    return result;     
}

unsigned char *test_decode_base64() {
    unsigned char *input = "Zm9v";
    int len = strlen(input);
    int result_len;
   
    unsigned char *result = decode_base64(input, len, &result_len);       
       
    return result;   
}

int main() {
    plan(2);
    is(test_encode_base64(), "AA==", "encode null byte");
    is(test_decode_base64(), "foo", "decode foo");
    done_testing();      
}
