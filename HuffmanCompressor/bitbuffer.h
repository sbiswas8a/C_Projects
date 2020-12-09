/** Header file for BitBuffer component
 *
 * @file bitbuffer.h
 * @author Dr. Sturgill
 * @author Sumit Biswas
 */

#ifndef _BITBUFFER_H_
#define _BITBUFFER_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/** Initial capacity of the data array of a BitBuffer, measured in bytes */
#define INI_CAP 4

/** Number of bits in a byte.  */
#define B_BITS 8

/** Maximum number of bits in a 4 byte integer */
#define MAX_INT_BITS 32

/** Representation of a resizable array of bytes, with functions to
    make it easy to access individual bits. */
typedef struct
{
    /** Resizable array of bytes stored in this buffer. */
    unsigned char *data;

    /** Number of bits currently stored in the data array (may not
      always be a multiple of 8). */
    int bitCount;

    /** Capacity of the data array, measured in bytes. */
    int cap;
} BitBuffer;

/** Function that dynamically allocates a new bit buffer, initializes it to empty,,
 * and returns it to the caller
 * @return returns a newly created empty BitBuffer struct.
 */
BitBuffer *makeBitBuffer();

/** Function that frees any resources used by the given bit buffer
 * @param buffer is the given bit buffer
 */
void freeBitBuffer(BitBuffer *buffer);

/** Function that returns the number of bits currently stored in the buffer
 * @param buffer is the buffer whose bit count is returned
 * @return returns the number of bits currently stored in the given buffer
 */
int getBitCount(BitBuffer const *buffer);

/** Function that returns either 0 or 1 based on the bit at the given index in the buffer
 * @param buffer is the BitBuffer being checked
 * @param idx is the index being checked
 * @return returns either 0 or 1 based on the bit at the given index
 */
bool getBit(BitBuffer const *buffer, int idx);

/** Function that will set the bit at the given index to the given value (0 or 1).
 * @param buffer is the buffer whose bits are being manipulated
 * @param idx is the index at which the bit is to be changed
 * @param value is the value to set at the given index
 */
void setBit(BitBuffer const *buffer, int idx, bool value);

/** Function that adds a bit to the end of the given bit buffer,
 * resizing the data array if necessary
 * @param buffer is the buffer being appended to
 * @param value is the bit value being appended
 */
void appendBit(BitBuffer *buffer, bool value);

/** Function that reads an input file, stores its contents in the data array of a new bit buffer
 * and returns it to the caller.
 * @param filename is the name of the input file
 * @return returns the newly created BitBuffer with the contents of the input file
 */
BitBuffer *loadBitBuffer(char const *filename);

/** Function that saves the contents of the given but buffer to a binary file with the given name
 * @param buffer is the BitBuffer being written to the file
 * @param filename is the name of the file being written to
 */
void saveBitBuffer(BitBuffer *buffer, char const *filename);

#endif
