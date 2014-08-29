#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../lib/tap.h"

unsigned char *test_xor_equal_length() {
    size_t result_len;
    unsigned char *input_hex = "1c0111001f010100061a024b53535009181c";
    unsigned char *key_hex = "686974207468652062756c6c277320657965";   
    unsigned char *input = hex_to_bytes(input_hex, strlen(input_hex), &result_len);
    unsigned char *key = hex_to_bytes(key_hex, strlen(key_hex), &result_len);    
    unsigned char *result = xor(input, key, result_len, &result_len);    
    
    size_t len = strlen(result);    
    unsigned char *result_hex = bytes_to_hex(result, len, &result_len);

    return result_hex;
}

int main() {    
    plan(1);
    is(test_xor_equal_length(), "746865206b696420646f6e277420706c6179", "test_xor_equal_length()");
    done_testing();      
}
