
#include <stdio.h>
#include "cryptoutil.h"

int main() {

    uint8_t in[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    uint8_t data[(sizeof in) >> 1];
    uint8_t out[cru_B64EncodedLength((sizeof in) >> 1) + 1];
    uint8_t expected[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

    printf("Input: %s\n", in);

    cru_HexDecode(in, data, sizeof in);
    cru_B64Encode(data, out, sizeof data);

    printf("Output:   %s\n", out);
    printf("Expected: %s\n", expected);

    return 0;
}
