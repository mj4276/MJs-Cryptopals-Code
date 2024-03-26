/*
cryptoutil.c - Utilities for use in the cryptopals challenges.
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cryptoutil.h"

uint32_t cru_B64EncodedLength(uint32_t len) {
    return ((((len - 1) / 3) + 1) * 12) / 3;
}

void cru_B64Encode(uint8_t* inbuf, uint8_t* outbuf, uint32_t len) {
    char b64dict[] =  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    // Read bytes from inbuf and process in 24-bit blocks
    uint32_t w_pos = 0;
    uint32_t block = 0;
    for (uint32_t i = 0; i < len; i++) {
        block |= ((uint32_t)inbuf[i]) << (8 * (2 - (i % 3))); 
        if (i % 3 == 2) {
            for (uint8_t j = 0; j < 4; j++) {
                uint8_t sextet = (block >> (6 * (3 - j))) & 0x3F;
                outbuf[w_pos] = b64dict[sextet];
                w_pos++;
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
            outbuf[w_pos] = b64dict[sextet];
            w_pos++;
        }
        for (; j < 4; j++) {
            outbuf[w_pos] = '=';
            w_pos++;
        }
    }
    outbuf[w_pos] = '\0';
}


void cru_HexDecode(uint8_t *inbuf, uint8_t* outbuf, uint32_t len) {
    
}

#ifdef DEBUG
int main(int argc, char* argv[]) {
    char in[] = "Hello World!\n";
    uint32_t outlen = cru_B64EncodedLength(strlen(in));
    printf("In-len: %ld, Out-len: %d\n", strlen(in), outlen);
    char out[outlen + 1];
    cru_B64Encode(in, out, strlen(in));
    printf("In: %s\nOut: %s\n", in, out);
}
#endif //DEBUG
