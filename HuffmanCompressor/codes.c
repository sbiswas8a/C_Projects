/** Codes component that reads in the file containing the codes
 * that represent all byte values
 *
 * @file codes.c
 * @author Sumit Biswas
 */

#include "codes.h"

/** 2D char Array that stores the codes */
static char arr[MAX_VALS][CODE_MAX + 1];
/** Integer that keeps track of the minimum code length */
static int minCodeLen = CODE_MAX + 1;

/** Function that checks if a given string is a prefix of another string
 * @param sub is the string that could be a prefix
 * @param string is the string that could have sub as a prefix
 * @return returns true if string has sub as a prefix, false otherwise
 */
static inline bool isPrefix(const char *sub, const char *string)
{
    return strncmp(sub, string, strlen(sub)) == 0;
}

/** Function that checks the read in codes to see if they are valid or not
 * @returns true if the codes are valid, false otherwise
 */
static bool checkCodes()
{
    for (int i = 0; i < MAX_VALS; i++)
    {
        char *check = arr[i];
        for (int j = 0; j < i; j++)
        {
            if (isPrefix(check, arr[j]))
            {
                return false;
            }
        }
        for (int j = i + 1; j < MAX_VALS; j++)
        {
            if (isPrefix(check, arr[j]))
            {
                return false;
            }
        }
    }
    return true;
}

int getMinCodeLen()
{
    return minCodeLen;
}

void loadCodes(char const *filename)
{
    int ch;
    int lineCount = 0, col = 0, currLen = 0;
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch != '\n' && ch != '0' && ch != '1')
        {
            fclose(fp);
            fprintf(stderr, "Invalid code file: %s\n", filename);
            exit(EXIT_FAILURE);
        }
        if (ch == '\n')
        {
            arr[lineCount][col] = '\0';
            if ((ch = fgetc(fp)) != EOF)
            {
                lineCount++;
                ungetc(ch, fp);
            }
            if (lineCount == MAX_VALS)
            {
                fclose(fp);
                fprintf(stderr, "Invalid code file: %s\n", filename);
                exit(EXIT_FAILURE);
            }
            minCodeLen = currLen < minCodeLen ? currLen : minCodeLen;
            col = 0, currLen = 0;
        }
        else
        {
            arr[lineCount][col] = ch;
            col++, currLen++;
            if (col > CODE_MAX)
            {
                fclose(fp);
                fprintf(stderr, "Invalid code file: %s\n", filename);
                exit(EXIT_FAILURE);
            }
        }
    }
    if (lineCount != MAX_VALS - 1)
    {
        fclose(fp);
        fprintf(stderr, "Invalid code file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    if (!checkCodes())
    {
        fprintf(stderr, "Invalid code file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
}

void freeCodes()
{
    // Doesn't do anything since the array for codes isn't dynamically allocated
}

char const *getCode(unsigned char byte)
{
    unsigned int index = byte;
    return arr[index];
}

int lookupCode(char const *bits)
{
    for (int i = 0; i < MAX_VALS; i++)
    {
        if (strcmp(bits, arr[i]) == 0)
        {
            return i;
        }
        else if (isPrefix(bits, arr[i]))
        {
            return CODE_PREFIX;
        }
    }
    return CODE_INVALID;
}
