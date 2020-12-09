/** Program that takes in a compressed input file and decompresses it to the original size
 *
 * @file inflate.c
 * @author Sumit Biswas
 */

#include "bitbuffer.h"
#include "codes.h"
#include <math.h>

/** Constant for valid number of arguments */
#define VALID_ARGC 4
/** Constant for argument index of input file */
#define INFILE 2
/** Constant for argument index of output file */
#define OUTFILE 3

/** Function that finds the size of the original file before compression
 * @param buffer is the buffer from where the stored size is extracted
 * @return returns the size of the original file before compression
 */
static int findFileSize(BitBuffer const *buffer)
{
    int num = 0;
    int idx = 0;
    for (int i = MAX_INT_BITS - 1; i >= 0; i--)
    {
        if (getBit(buffer, idx++))
        {
            num += (int)pow(2, i);
        }
    }
    return num;
}

/** Starts the program
 * @param argc is the number of arguments
 * @param argv is the 2d array containing the arguments
 */
int main(int argc, char *argv[])
{
    if (argc != VALID_ARGC)
    {
        fprintf(stderr, "usage: inflate <code-file> <infile> <outfile>\n");
        exit(EXIT_FAILURE);
    }
    // loading the codes
    loadCodes(argv[1]);
    // loading the compressed file
    BitBuffer *buff = loadBitBuffer(argv[INFILE]);

    FILE *fw = fopen(argv[OUTFILE], "wb");
    if (!fw)
    {
        perror(argv[OUTFILE]);
        freeBitBuffer(buff);
        exit(EXIT_FAILURE);
    }

    int originalSize = findFileSize(buff);
    int idx = MAX_INT_BITS;
    int endIdx = getBitCount(buff);
    int codesCovered = 0, arrIdx = 0;
    char code[CODE_MAX + 1];
    int result;
    int minCodeLen = getMinCodeLen();

    while (codesCovered != originalSize && idx < endIdx)
    {
        for (int i = 0; i < minCodeLen - 1 && idx < endIdx; i++, idx++)
        {
            code[arrIdx++] = getBit(buff, idx) ? '1' : '0';
        }
        code[arrIdx] = '\0';
        // rechecking point
        recheck:
        result = lookupCode(code);
        if (result == CODE_PREFIX && idx < endIdx)
        {
            code[arrIdx++] = getBit(buff, idx) ? '1' : '0';
            code[arrIdx] = '\0';
            idx++;
            goto recheck;
        }
        else if (result != CODE_INVALID && result != CODE_PREFIX)
        {
            fwrite(&result, 1, 1, fw);
            arrIdx = 0;
            codesCovered++;
        }
        else if (result == CODE_INVALID)
        {
            fprintf(stderr, "Invalid code file: %s\n", argv[1]);
            fclose(fw);
            freeBitBuffer(buff);
            exit(EXIT_FAILURE);
        }
    }
    fclose(fw);
    freeBitBuffer(buff);
    if (codesCovered != originalSize)
    {
        fprintf(stderr, "Invalid input file: %s\n", argv[INFILE]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
