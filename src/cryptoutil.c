/*
cryptoutil.c - Utilities for use in the cryptopals challenges.
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cryptoutil.h"

static uint8_t HexCharToNibble(const uint8_t c);

uint32_t cru_B64EncodedLength(uint32_t len) {
    return ((((len - 1) / 3) + 1) * 12) / 3;
}

uint32_t cru_B64DecodedLength(uint32_t len) {
    // Assume correct padding and that (len % 4 != 0) implies a null-termination
    return (len / 4) * 3;
}

void cru_B64Encode(uint8_t* inbuf, uint8_t* outbuf, uint32_t len) {
    const char b64lut[] =  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    // Read bytes from inbuf and process in 24-bit blocks
    uint32_t w_pos = 0;
    uint32_t block = 0;
    for (uint32_t i = 0; i < len; i++) {
        block |= ((uint32_t)inbuf[i]) << (8 * (2 - (i % 3))); 
        if (i % 3 == 2) {
            for (uint8_t j = 0; j < 4; j++) {
                uint8_t sextet = (block >> (6 * (3 - j))) & 0x3F;
                outbuf[w_pos] = b64lut[sextet];
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
            outbuf[w_pos] = b64lut[sextet];
            w_pos++;
        }
        for (; j < 4; j++) {
            outbuf[w_pos] = '=';
            w_pos++;
        }
    }
    outbuf[w_pos] = '\0';
}

static uint8_t HexCharToNibble(const uint8_t c) {
    // I might have otherwise used sprintf(), but this is a low-level
    // library, and this should be faseter:
    return c & 0x40 ? (c & 0x0F) + 9 : c & 0x0F;
}

void cru_HexDecode(uint8_t *inbuf, uint8_t *outbuf, uint32_t len) {
    for (uint32_t i = 0; i < ((len>>1)<<1); i += 2) { // len is rounded to the nearest multiple of 2
        outbuf[i>>1] = (HexCharToNibble(inbuf[i]) << 4) | HexCharToNibble(inbuf[i+1]);
    }
}

#ifdef DEBUG
int main(int argc, char* argv[]) {
    char in[] = "48656c6c6f20576f726c6421";
    uint32_t outlen = cru_B64EncodedLength(strlen(in));
    printf("In-len: %ld, Out-len: %d\n", strlen(in), outlen);
    char out[20] = { 0 };
    cru_HexDecode(in, out, strlen(in));
    printf("In: %s\nOut: %s\n", in, out);
}
#endif //DEBUG
