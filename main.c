#include <stdio.h>
#include <stdlib.h>
#include "base64.h"
/*
 * 
 */
int main(int argc, char** argv) {
    unsigned char input[2] = {'\xff', '\x20'};
    printBits(1, &input[0]);
    printBits(1, &input[1]);
    
    
    size_t modulusLen = 0 % 3 ;
    size_t t1 = (0x0f&0xff)<<2;
    size_t t2 = (modulusLen&2)>>1;
    puts("");
    printBits(1, &t1);
    printBits(1, &t2);
    size_t pad = ((modulusLen&1)<<1) + ((modulusLen&2)>>1);
    
    
    size_t out_len;
    
    encode_base64(input, 2, &out_len);
    return (EXIT_SUCCESS);
}



