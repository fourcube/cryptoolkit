#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/tap.h"

bool test_hex_to_bytes_empty() {
    unsigned char* hex = "";    
    size_t result_len;
    unsigned char* result = hex_to_bytes(hex, 0, &result_len);  
    
    return result_len == 0;
}

bool test_hex_to_bytes() {
    unsigned char* hex = "49";
    size_t result_len;
    unsigned char *result;
    
    result = hex_to_bytes(hex, 2, &result_len);  
    
    return result[0] == 73;
}

bool test_bytes_to_hex() {
    unsigned char bytes[1] = {73};
    size_t result_len;
    unsigned char* result = bytes_to_hex(bytes, 1, &result_len);  
    
    return strcmp(result, "49") == 0;
}

bool test_hex_to_bytes_odd() {
    unsigned char* hex = "493";
    size_t result_len;
    unsigned char* result = hex_to_bytes(hex, 0, &result_len);  
    
    return result_len == 0;
}

int main() {
    plan(4);
    ok(test_hex_to_bytes(), "test_hex_to_bytes()");
    ok(test_hex_to_bytes_empty(), "test_hex_to_bytes_empty()");
    ok(test_hex_to_bytes_odd(), "test_hex_to_bytes_odd()");
    ok(test_bytes_to_hex(), "test_bytes_to_hex()");
    done_testing();
}
