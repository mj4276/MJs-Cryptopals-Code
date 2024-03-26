


#include <stdio.h>
#include <unistd.h>
#include "cryptoutil.h"

#define BUFFSIZE 57

int main(int argc, char* argv[]) {

    uint8_t inbuf[BUFFSIZE];    
    uint32_t bytes_read;

    uint8_t outbuf[cru_B64EncodedLength(BUFFSIZE) + 1];
    char newline = 0x0A;


    while ((bytes_read = read(STDIN_FILENO, inbuf, sizeof inbuf))) {
        cru_B64Encode(inbuf, outbuf, bytes_read);
        write(STDOUT_FILENO, outbuf, cru_B64EncodedLength(bytes_read));
        write(STDOUT_FILENO, &newline, 1);
    }

    return 0;
}
