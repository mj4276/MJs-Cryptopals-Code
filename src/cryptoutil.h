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

/* Encode 'len' bytes from inBuf to Base64 and write the result
 * to outBuf, including a null-termination.
 */
void cru_B64Encode(char* inBuf, char* outBuf, uint32_t len);


#endif //CRYPTOUTIL_H
