#include <stdio.h>
#include <unistd.h>
#include "cryptoutil.h"
#include "string.h"

#define LINEWIDTH 76
#define BUFFSIZE 65536

static void HexToB64(uint8_t* inbuf, uint8_t* outbuf, uint32_t len);
static uint32_t HexToB64TranscodedLength(uint32_t);
static uint32_t B64ToHexTranscodedLength(uint32_t len);

static void HexToB64(uint8_t* inbuf, uint8_t* outbuf, uint32_t len) {
    uint8_t buf[len>>1];
    cru_HexDecode(inbuf, buf, len);
    cru_B64Encode(buf, outbuf, len>>1);
}

static uint32_t HexToB64TranscodedLength(uint32_t len) {
    return cru_B64EncodedLength(len >> 1);
}

static uint32_t B64ToHexTranscodedLength(uint32_t len) {
    return cru_B64DecodedLength(len) << 2;
}

int main(int argc, char* argv[]) {

    void (*transcode) (uint8_t* inbuf, uint8_t* outbuf, uint32_t len);
    uint32_t (*out_len) (uint32_t len);
    uint32_t (*in_len) (uint32_t len);

    if (argc > 1 && strcmp("--hex", argv[1]) == 0) {
        transcode = HexToB64;
        out_len = HexToB64TranscodedLength;
        in_len = B64ToHexTranscodedLength;
    } else {
        transcode = cru_B64Encode;
        out_len = cru_B64EncodedLength;
        in_len = cru_B64DecodedLength;
    }

    uint8_t  inbuf[in_len(LINEWIDTH)];
    uint32_t bytes_read;
    uint8_t  outbuf[BUFFSIZE];
    uint32_t whead = 0;

    while (!feof(stdin)) {

        // Read until we get a full output line's worth of input or EOF
        bytes_read = 0;
        while (bytes_read < sizeof inbuf && !feof(stdin)) {
           bytes_read += fread((uint8_t*)(inbuf + bytes_read), 1,
                                (sizeof inbuf) - bytes_read, stdin); 
        }
    
        // Transcode into outbuf
        transcode(inbuf, (uint8_t*)&outbuf[whead], bytes_read);

        if (bytes_read == sizeof inbuf) { // Don't calculate out_len() each cycle
            whead += LINEWIDTH + 1;
        } else {
            whead += out_len(bytes_read) + 1;
        }
        outbuf[whead-1] = '\n';
        
        // Flush outbuf to stdout every now and then
        if (whead > BUFFSIZE - LINEWIDTH - 1) {
            fwrite(outbuf, 1, whead, stdout);
            whead = 0;
        }
    }
    
    // Finish by emptying outbuf one last time
    fwrite(outbuf, 1, whead, stdout);

    return 0;
}
