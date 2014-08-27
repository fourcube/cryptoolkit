/*
 * Based on https://github.com/superwills/NibbleAndAHalf/blob/master/NibbleAndAHalf/base64.h
 */

#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define TWO_LEAST_SIGNIFICANT_BITS(n) (0x3&n)
#define FOUR_LEAST_SIGNIFICANT_BITS(n) (0x0f&n)
#define SIX_LEAST_SIGNIFICANT_BITS(n) (0x3f&n)

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};


const static unsigned char decoding_table[]={
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //10 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //20 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //30 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //40 
  0,   0,   0,  62,   0,   0,   0,  63,  52,  53, //50 
 54,  55,  56,  57,  58,  59,  60,  61,   0,   0, //60 
  0,   0,   0,   0,   0,   0,   1,   2,   3,   4, //70 
  5,   6,   7,   8,   9,  10,  11,  12,  13,  14, //80 
 15,  16,  17,  18,  19,  20,  21,  22,  23,  24, //90 
 25,   0,   0,   0,   0,   0,   0,  26,  27,  28, //100 
 29,  30,  31,  32,  33,  34,  35,  36,  37,  38, //110 
 39,  40,  41,  42,  43,  44,  45,  46,  47,  48, //120 
 49,  50,  51,   0,   0,   0,   0,   0,   0,   0, //130 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //140 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //150 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //160 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //170 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //180 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //190 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //200 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //210 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //220 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //230 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //240 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //250 
  0,   0,   0,   0,   0,   0, 
}; 

unsigned char *encode_base64(const void* binaryData, int len, size_t *output_length) {
    size_t modulusLen = len % 3 ;
    // 2 -> 1, 1 -> 2, 0 -> 0
    size_t pad = modulusLen == 2 ? 1 : modulusLen == 1 ? 2 : 0;
    int count = 0;
    size_t rc = 0;

    *output_length = 4*(len + pad)/3;    
    const unsigned char *buf = (const unsigned char*) binaryData;

    char *result = (char*) malloc(*output_length + 1);

    if(!result) {  
      puts("Couldn't allocate memory.") ;      
      return 0;
    }

    for(count = 0; count <= (len-3); count+=3) {
      unsigned char BYTE0=buf[count];
      unsigned char BYTE1=buf[count+1];
      unsigned char BYTE2=buf[count+2];

      result[rc++] = encoding_table[BYTE0 >> 2] ;
      result[rc++] = encoding_table[(TWO_LEAST_SIGNIFICANT_BITS(BYTE0) << 4) + (BYTE1 >> 4)];
      result[rc++] = encoding_table[(FOUR_LEAST_SIGNIFICANT_BITS(BYTE1) << 2) + (BYTE2 >> 6)];
      result[rc++] = encoding_table[SIX_LEAST_SIGNIFICANT_BITS(BYTE2)];
    }

    if(pad == 2) {
      result[rc++] = encoding_table[buf[count] >> 2] ;
      result[rc++] = encoding_table[FOUR_LEAST_SIGNIFICANT_BITS(0x3&buf[count])<<4] ;
      result[rc++] = '=';
      result[rc++] = '=';
    }
    else if(pad == 1) {
      result[rc++]  = encoding_table[buf[count] >> 2] ;
      result[rc++]  = encoding_table[(FOUR_LEAST_SIGNIFICANT_BITS(0x3&buf[count]) << 4) + (buf[count+1] >> 4)] ;
      result[rc++]  = encoding_table[SIX_LEAST_SIGNIFICANT_BITS(buf[count+1]) << 2] ;
      result[rc++] = '=';
    }

    // terminate with \x00
    result[rc]=0;
    return result;
}

unsigned char* decode_base64(const char* input, int len, int *result_len)
{
  const unsigned char *safeAsciiPtr = (const unsigned char*) input ;
  unsigned char *bin ;
  int cb=0;
  int charNo;
  int pad = 0 ;

  if(len < 2) { // 2 accesses below would be OOB.
    // catch empty string, return NULL as result.
    puts("ERROR: You passed an invalid base64 string (too short). You get NULL back.") ;
    *result_len=0;
    return 0 ;
  }
  if(safeAsciiPtr[len-1]=='=')  ++pad ;
  if(safeAsciiPtr[len-2]=='=')  ++pad ;
  
  *result_len = 3*len/4 - pad ;
  bin = (unsigned char*)malloc(*result_len) ;
  if(!bin)
  {
    puts("ERROR: unbase64 could not allocate enough memory.") ;
    puts("I must stop because I could not get enough") ;
    return 0;
  }
  
  for(charNo=0; charNo <= len - 4 - pad ; charNo+=4)
  {
    int A=decoding_table[safeAsciiPtr[charNo]];
    int B=decoding_table[safeAsciiPtr[charNo+1]];
    int C=decoding_table[safeAsciiPtr[charNo+2]];
    int D=decoding_table[safeAsciiPtr[charNo+3]];
    
    bin[cb++] = (A<<2) | (B>>4) ;
    bin[cb++] = (B<<4) | (C>>2) ;
    bin[cb++] = (C<<6) | (D) ;
  }
  
  if(pad==1)
  {
    int A=decoding_table[safeAsciiPtr[charNo]];
    int B=decoding_table[safeAsciiPtr[charNo+1]];
    int C=decoding_table[safeAsciiPtr[charNo+2]];
    
    bin[cb++] = (A<<2) | (B>>4) ;
    bin[cb++] = (B<<4) | (C>>2) ;
  }
  else if(pad==2)
  {
    int A=decoding_table[safeAsciiPtr[charNo]];
    int B=decoding_table[safeAsciiPtr[charNo+1]];
    
    bin[cb++] = (A<<2) | (B>>4) ;
  }
  
  return bin ;
}

#endif