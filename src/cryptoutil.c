/*
cryptoutil.c - Utilities for use in the cryptopals challenges.
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cryptoutil.h"

void cru_B64Encode(char* inBuf, char* outBuf, int len) {
    char b64dict[] =  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    // Read bytes from inBuf and process in 24-bit blocks
    uint32_t wPos = 0;
    uint32_t block = 0;
    for (uint8_t i = 0; i < len; i++) {
        block |= ((uint32_t)inBuf[i]) << (8 * (2 - (i % 3))); 
        if (i % 3 == 2) {
            for (int j = 0; j < 4; j++) {
                uint8_t sextet = (block >> (6 * (3 - j))) & 0x3F;
                outBuf[wPos] = b64dict[sextet];
                wPos++;
            }
            block = 0;
        }
    }
    // If applicable, process the last partial block, padding with '='
    uint8_t remainder = len % 3;
    if (remainder) {
        uint8_t valid_sextets = remainder == 1 ? 2 : 3;
        uint8_t j;
        for (j = 0; j < valid_sextets; j++) {
            uint8_t sextet = (block >> (6 * (3 - j))) & 0x3F;
            outBuf[wPos] = b64dict[sextet];
            wPos++;
        }
        for (; j < 4; j++) {
            outBuf[wPos] = '=';
            wPos++;
        }
    }
}



#ifdef DEBUG
int main(int argc, char* argv[]) {
    char in[] = "Hello World!\n";
    int outlen = ((strlen(in)+3)*4)/3;
    printf("In-len: %ld, Out-len: %d\n", strlen(in), outlen);
    char out[outlen];
    cru_B64Encode(in, out, strlen(in));
    printf("In: %s\nOut: %s\n", in, out);
}
#endif //DEBUG
