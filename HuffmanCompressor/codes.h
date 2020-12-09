/** Header file for the codes component
 *
 * @file codes.h
 * @author Dr. Sturgill
 * @author Sumit Biswas
 */

#ifndef _CODES_H_
#define _CODES_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/** Number of bits in a byte.  */
#define BBITS 8

/** Maximum number of bits in a code. */
#define CODE_MAX 24

/** Maximum number of byte values (0 - 255) */
#define MAX_VALS 256

/** Return value from lookupCode() indicating that the given
  * string is the prefix of a code (so, it needs more bits
  * to match a code exactly. */
#define CODE_PREFIX -1

/** Return value from lookupCode() indicating that the given
  * string doesn't match (and isn't a prefix of) any code.  This
  * should only happen in case of an error. */
#define CODE_INVALID -2

/** Function that returns the length of the smallest code
 * @return returns the length of the smallest code
 */
int getMinCodeLen();

/** Given a string of '0' and '1' characters representing string of bits,
  * report whether this sequence of bits matches the code for any
  * byte.
  * @param bits String containing a sequence of '0' and '1'.
  * @return the byte value for a matching code, or values CODE_PREFIX
  * or CODE_INVALID described above. */
int lookupCode(char const *bits);

/** Function that reads the code file and stores it in arrays
 * Terminates the program if the code file is invalid
 * @param filename is the name of the file containing the codes
 */
void loadCodes(char const *filename);

/** Function that frees any resources used by this component */
void freeCodes();

/** Function that returns a string representing the variable length code for the given byte value
 * @param byte is the given byte value
 * @return returns a string representing the variable length code for the given byte value
 */
char const *getCode(unsigned char byte);

#endif
