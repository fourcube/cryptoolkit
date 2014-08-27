#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../crypt_error.h"
#include "../lib/tap.h"

bool test_hex_to_bytes_empty() {
    unsigned char* hex = "";
    unsigned char result[0];
    crypt_error code = hex_to_bytes(hex, result, 0);
    
    
    return code == input_empty;
}

bool test_hex_to_bytes_result_buffer_too_small() {
    unsigned char* hex = "deadbeef";
    unsigned char result[0];
    
    crypt_error code = hex_to_bytes(hex, result, 0);
       
    return code == result_buffer_too_small;
}

bool test_hex_to_bytes() {
    unsigned char* hex = "49";
    unsigned char result[2];
    
    crypt_error code = hex_to_bytes(hex, result, 2);
    
    return code == none && result[0] == 73;
}

bool test_hex_to_bytes_odd() {
    unsigned char* hex = "493";
    unsigned char result[0];
    crypt_error code = hex_to_bytes(hex, result, 0);
    
    
    return code == input_not_even;
}

int main() {
    plan(4);
    ok(test_hex_to_bytes(), "test_hex_to_bytes()");
    ok(test_hex_to_bytes_empty(), "test_hex_to_bytes_empty()");
    ok(test_hex_to_bytes_odd(), "test_hex_to_bytes_odd()");
    ok(test_hex_to_bytes_result_buffer_too_small(), "test_hex_to_bytes_result_buffer_too_small()");    
    done_testing();
}
