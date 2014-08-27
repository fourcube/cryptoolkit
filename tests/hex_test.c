#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../crypt_error.h"
#include "CUnit/Basic.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_hex_to_bytes_empty() {
    unsigned char* hex = "";
    unsigned char result[0];
    crypt_error code = hex_to_bytes(hex, result, 0);
    
    
    if (code == input_empty) {
        CU_ASSERT(1);
    } else {
        CU_ASSERT(0);
    }
}

void test_hex_to_bytes_result_buffer_too_small() {
    unsigned char* hex = "deadbeef";
    unsigned char result[0];
    
    crypt_error code = hex_to_bytes(hex, result, 0);
       
    if (code == result_buffer_too_small) {
        CU_ASSERT(1);
    } else {
        CU_ASSERT(0);
    }
}

void test_hex_to_bytes() {
    unsigned char* hex = "49";
    unsigned char result[2];
    
    crypt_error code = hex_to_bytes(hex, result, 2);
    
    if (code == none && result[0] == 73) {
        CU_ASSERT(1);
    } else {
        CU_ASSERT(0);
    }
}

void test_hex_to_bytes_odd() {
    unsigned char* hex = "493";
    unsigned char result[0];
    crypt_error code = hex_to_bytes(hex, result, 0);
    
    
    if (code == input_not_even) {
        CU_ASSERT(1);
    } else {
        CU_ASSERT(0);
    }
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("hex_test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_hex_to_bytes_empty", test_hex_to_bytes_empty))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if ((NULL == CU_add_test(pSuite, "test_hex_to_bytes", test_hex_to_bytes))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if ((NULL == CU_add_test(pSuite, "test_hex_to_bytes_odd", test_hex_to_bytes_odd))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if ((NULL == CU_add_test(pSuite, "test_hex_to_bytes_result_buffer_too_small", test_hex_to_bytes_result_buffer_too_small))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
