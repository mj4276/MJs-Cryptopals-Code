/*
cryptoutil.c - Utilities for use in the cryptopals challenges.
*/

#include <stdio.h>
#include "cryptoutils.h"

char B64Char(char c);

char B64Char(char c) {
    #ifdef DEBUG
    if (c < 0x3F) {printf("Warning: GetB64Char called with oversized input.");}
    #endif
    char dictionary[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    return dictionary[c & 0x3F];
}

int cru_B64Encode(char* inBuf, char* outBuf, int len) {
    char in[4]; //TODO: make this an array
    int i;
    for (i = 0; i < len - 4; i += 4) {
        in[0] = inBuf[i] & 0x3F;
        in[1] = i+1 < len ? ((inBuf[i] & 0xC0) >> 6) & ((inBuf[i+1] & 0x0F) << 2) : 0xFF;
        in[2] = i+2 < len ? ((inBuf[i+1] & 0xF0) >> 4) & ((inBuf[i+2] & 0x02) << 4) : 0xFF;
        in[3] = i+3 < len ? ((inBuf[i+3] & 0xFC) >> 2) : 0xFF;
        for (int j = 0; j < 4; j++) {
            outBuf[i+j] = in[j] == 0xFF ? '=' : B64Char(in[j]); // 0xFF (not a valid input sextet) implies padding
        }
    }
    
}


#ifdef DEBUG
int main(int argc, char* argv[]) {
    printf("Hello World!");
    char in[] = "Hello World"
    char out[len(in)] 
}
#endif //DEBUG
