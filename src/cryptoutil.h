#ifndef CRYPTOUTIL_H
#define CRYPTOUTIL_H

#include <stdint.h>

/* Return the number of bytes required to store the Base64
 * encoding of an input buffer of lenth 'len'.
 * Note: Be sure to add 1 byte for null termination when
 * allocating space for the output of cru_B64Encode(). It
 * is ommitted here just as in strlen() in string.h.
 */
uint32_t cru_B64EncodedLength(uint32_t len);

/* Encode 'len' bytes from inbuf to Base64 and write the result
 * to outbuf, including a null-termination.
 */
void cru_B64Encode(uint8_t* inbuf, uint8_t* outbuf, uint32_t len);

/* Decode 'len' bytes from the ascii hexadecimal in inbuf and
 * write the raw data to outbuf. Invalid characters are decoded
 * as 0. This function rounds 'len' down to the nearest multiple
 * of two, so the output of strlen can be used as 'len' directly
 */
void cru_HexDecode(uint8_t *inbuf, uint8_t* outbuf, uint32_t len);

#endif //CRYPTOUTIL_H
