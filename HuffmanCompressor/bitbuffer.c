/** BitBuffer component that includes a representation of a bit buffer
 * Reads an input file and stores its contents in a new BitBuffer
 *
 * @file bitbuffer.c
 * @author Sumit Biswas
 */

#include "bitbuffer.h"

BitBuffer *makeBitBuffer()
{
    BitBuffer *buffer = (BitBuffer *)malloc(sizeof(BitBuffer));
    buffer->bitCount = 0;
    buffer->cap = INI_CAP;
    unsigned char *arr = (unsigned char *)malloc(INI_CAP);
    for (int i = 0; i < INI_CAP; i++)
    {
        arr[i] = 0x00;
    }
    buffer->data = arr;
    return buffer;
}

void freeBitBuffer(BitBuffer *buffer)
{
    free(buffer->data);
    free(buffer);
}

int getBitCount(BitBuffer const *buffer)
{
    return buffer->bitCount;
}

bool getBit(BitBuffer const *buffer, int idx)
{
    int byteIndex = idx / B_BITS;
    int bitIndex = B_BITS - (idx - (byteIndex * B_BITS)) - 1;
    unsigned char ch = buffer->data[byteIndex];
    return ((ch >> bitIndex) & 1);
}

void setBit(BitBuffer const *buffer, int idx, bool value)
{
    int byteIndex = idx / B_BITS;
    int bitIndex = B_BITS - (idx - (byteIndex * B_BITS)) - 1;
    unsigned char ch = buffer->data[byteIndex];
    if (value)
    {
        ch |= 1 << bitIndex;
    }
    else
    {
        ch &= ~(1 << bitIndex);
    }
    buffer->data[byteIndex] = ch;
}

void appendBit(BitBuffer *buffer, bool value)
{
    if (buffer->bitCount / B_BITS == buffer->cap)
    {
        int oldCap = buffer->cap;
        buffer->cap *= 2;
        buffer->data = (unsigned char *)realloc(buffer->data, buffer->cap);
        for (int i = oldCap; i < buffer->cap; i++)
        {
            buffer->data[i] = 0x00;
        }
    }
    setBit(buffer, buffer->bitCount, value);
    (buffer->bitCount)++;
}

BitBuffer *loadBitBuffer(char const *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    unsigned char *arr = (unsigned char *)malloc(size);
    int len = fread(arr, 1, size, fp);
    fclose(fp);
    BitBuffer *buff = makeBitBuffer();
    free(buff->data);
    buff->data = arr;
    buff->bitCount = len * B_BITS;
    return buff;
}

void saveBitBuffer(BitBuffer *buffer, char const *filename)
{
    int bC = getBitCount(buffer);
    if (bC % B_BITS != 0)
    {
        int num = B_BITS - (bC % B_BITS);
        for (int i = 0; i < num; i++)
        {
            appendBit(buffer, false);
        }
    }
    bC = (getBitCount(buffer)) / B_BITS;
    FILE *fp = fopen(filename, "wb");
    fwrite(buffer->data, 1, bC, fp);
    fclose(fp);
}
