#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_encode_base64() {
    unsigned char input[1] = {'\x00'};
    size_t len = 1;
    size_t result_length;
        
    unsigned char *result = encode_base64(input, len, &result_length);
    
    if (result_length == 4 && strcmp(result, "AA==") == 0) {
        CU_ASSERT(1);
    } else {
        CU_ASSERT(0);
    }
    
    free(result);
}

void test_decode_base64() {
    unsigned char *input = "AA==";
    int len = strlen(input);
    int result_len;
        
    unsigned char *result = decode_base64(input, len, &result_len);
    unsigned char expected[1] = {'\x00'};
    
    if (result_len == 1 && memcmp(result, expected, 1) == 0) {
        CU_ASSERT(1);
    } else {
        CU_ASSERT(0);
    }
    
    free(result);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("base64_test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_encode_base64", test_encode_base64))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite, "test_decode_base64", test_decode_base64))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
