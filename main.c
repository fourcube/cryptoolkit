#include <stdio.h>
#include <stdlib.h>
#include "base64.h"
/*
 * 
 */
int main(int argc, char** argv) {
    char *input = "foo";
    size_t out_len;
    
    unsigned char *result = encode_base64(input, 3, &out_len);
    puts(result);
    
    return (EXIT_SUCCESS);
}



