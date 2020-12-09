/** Program that takes in an input file and compresses it
 *
 * @file deflate.c
 * @author Sumit Biswas
 */

#include "bitbuffer.h"
#include "codes.h"

/** Constant for valid number of arguments */
#define VALID_ARGC 4
/** Constant for argument index of input file */
#define INFILE 2
/** Constant for argument index of output file */
#define OUTFILE 3

/** Function that returns a string containing the binary representation of the given number
 * @param num is the given number
 * @return returns a string containing the binary representation of the given number
 */
static char *decimalToBinary(int num)
{
    int idx = 0;
    char *binary = (char *)malloc(MAX_INT_BITS + 1);
    for (int i = MAX_INT_BITS - 1; i >= 0; i--)
    {
        int k = num >> i;
        if (k & 1)
        {
            binary[idx++] = '1';
        }
        else
        {
            binary[idx++] = '0';
        }
    }
    binary[MAX_INT_BITS] = '\0';
    return binary;
}

/** Starts the program
 * @param argc is the number of arguments
 * @param argv is the 2d array containing the arguments
 */
int main(int argc, char *argv[])
{
    if (argc != VALID_ARGC)
    {
        fprintf(stderr, "usage: deflate <code-file> <infile> <outfile>\n");
        exit(EXIT_FAILURE);
    }

    loadCodes(argv[1]);
    FILE *fr = fopen(argv[INFILE], "rb");
    if (!fr)
    {
        perror(argv[INFILE]);
        exit(EXIT_FAILURE);
    }

    fseek(fr, 0, SEEK_END);
    int size = (int)ftell(fr);
    fseek(fr, 0, SEEK_SET);
    char *sizeBinary = decimalToBinary(size);

    char const *code;
    BitBuffer *buff = makeBitBuffer();

    // appending first 32 bits of size
    char *start = sizeBinary;
    while (*start)
    {
        if (*start == '0')
        {
            appendBit(buff, false);
        }
        else
        {
            appendBit(buff, true);
        }
        start++;
    }
    free(sizeBinary); // freeing malloced size array

    // appending codes
    unsigned char ch;
    int len;
    while ((len = fread(&ch, 1, 1, fr)) == 1)
    {
        code = getCode(ch);
        while (*code)
        {
            if (*code == '0')
            {
                appendBit(buff, false);
            }
            else
            {
                appendBit(buff, true);
            }
            code++;
        }
    }
    fclose(fr);
    saveBitBuffer(buff, argv[OUTFILE]);
    freeBitBuffer(buff);
    return EXIT_SUCCESS;
}
