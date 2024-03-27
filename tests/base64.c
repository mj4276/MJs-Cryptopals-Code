#include <stdio.h>
#include <unistd.h>
#include "cryptoutil.h"
#include "string.h"

#define LINEWIDTH 76

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

    uint8_t inbuf[in_len(LINEWIDTH)];
    uint32_t bytes_read;
    uint8_t outbuf[LINEWIDTH + 1];
    char newline = 0x0A;

    while ((bytes_read = read(STDIN_FILENO, inbuf, sizeof inbuf))) {
        transcode(inbuf, outbuf, bytes_read);
        write(STDOUT_FILENO, outbuf, out_len(bytes_read));
        write(STDOUT_FILENO, &newline, 1);
    }

    return 0;
}
