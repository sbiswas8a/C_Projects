/** @file match.c
 * @author Sumit Biswas
 * Match component of the program that matches the specifications input by
 * the user
 */

#include "match.h"

/** Integer factor used to convert uppercase chars to lowercase */
 #define TO_LOWER_FACTOR 32
 /** ASCII Value of uppercase 'A' */
 #define ASCII_UC_A 65
 /** ASCII Value of uppercase 'Z' */
 #define ASCII_UC_Z 90
 /** ASCII Value of lowercase 'A' */
 #define ASCII_LC_A 97
 /** ASCII Value of lowercase 'Z' */
 #define ASCII_LC_Z 122

/** Function that takes in a character and returns if it is a letter ( a - z ) or not
 * @param ch is the character being checked
 * @return returns true if the character is a letter, false otherwise
 */
static bool isAlpha( char const ch ) {
    if ( ( ch >= ASCII_UC_A && ch <= ASCII_UC_Z ) || ( ch >= ASCII_LC_A && ch <= ASCII_LC_Z ) ) {
        return true;
    }
    return false;
}

/** Function that takes in a character and returns the lowercase version of it
 * if it is in uppercase
 * @param ch is the character passed in
 * @return returns the lowercase version of uppercase characters
 */
static char toLower( char const ch ) {
    if ( ch >= ASCII_UC_A && ch <= ASCII_UC_Z ) {
        return ( char ) ( ch + TO_LOWER_FACTOR );
    }
    return ch;
}

bool inRange( int idx, char const *start, char const *end )
{
    int rOne, rTwo;
    idx++;
    if ( sscanf( start, "%d", &rOne ) <= 0 ) {
        fprintf( stderr, "Invalid line number: %s\n", start );
        exit( EXIT_FAILURE );
    }
    if ( sscanf( end, "%d", &rTwo ) <= 0 ) {
        fprintf( stderr, "Invalid line number: %s\n", end );
        exit( EXIT_FAILURE );
    }
    if ( rOne == 0 || rTwo == 0 ) {
        fprintf( stderr, "Invalid line number: 0\n");
    }
    if ( rOne < 0 ) {
        rOne = lineCount() + rOne + 1;
    }
    if ( rTwo < 0 ) {
        rTwo = lineCount() + rTwo + 1;
    }
    if (rOne > rTwo) {
        return (idx >= rTwo && idx <= rOne);
    } else if ( rOne < rTwo ) {
        return (idx <= rTwo && idx >= rOne);
    } else {
        return idx == rOne;
    }
}

bool containsPattern ( char const *line, char const *str )
{
    int patternLength = 0;
    int lineLength = 0;
    for (int i = 0; line[i]; i++) {
        lineLength++;
    }
    for (int i = 0; str[i]; i++) {
        patternLength++;
    }

    // checking
    bool contains = false;
    int patternStartIndex = -1;
    int patternEndIndex = 0;
    int idx = 0;
    while ( patternStartIndex < lineLength - 1 ) {
        if (contains) {
            break;
        }
        patternStartIndex++;
        patternEndIndex = patternStartIndex;
        idx = 0;
        for ( int i = patternStartIndex; i < ( patternStartIndex + patternLength )
            && i < lineLength; i++ ) {
            if ( str[idx] == line[i] ) {
                contains = true;
                patternEndIndex++;
                idx++;
            } else {
                contains = false;
                break;
            }
        }
    }
    return patternEndIndex - patternStartIndex == patternLength;
}

// Plenty of patchy code in here, never got around to fixing it
// Do not think I remember the project requirements now
bool containsWord ( char const *line, char const *word )
{
    // finds lengths
    int wordLength = 0;
    int lineLength = 0;
    for (int i = 0; line[i]; i++) {
        lineLength++;
    }
    for (int i = 0; word[i]; i++) {
        wordLength++;
    }

    // invalid word check
    if ( !isAlpha( word[0] ) || !isAlpha( word[wordLength - 1] ) ) {
        fprintf( stderr, "%s%s\n", "Invalid word: ", word );
        exit( EXIT_FAILURE );
    }
    for ( int i = 0; i < wordLength; i++ ) {
        if ( !isAlpha( word[i] ) && word[i] != '\'' ) {
            fprintf( stderr, "%s%s\n", "Invalid word: ", word );
            exit( EXIT_FAILURE );
        }
    }

    char string[lineLength + 1];
    char sub[wordLength + 1];
    int j = 0;
    for ( j = 0; j < wordLength; j++ ) {
        sub[j] = toLower( word[j] );
    }
    sub[++j] = '\0';
    for ( j = 0; j < lineLength; j++ ) {
        string[j] = toLower( line[j] );
    }
    string[++j] = '\0';

    // checking
    bool contains = false;
    int wordStartIndex = -1;
    int checkEndIndex = 0;
    startCheck:
    while ( wordStartIndex < lineLength ) {
        if (contains) {
            break;
        }
        wordStartIndex++;
        checkEndIndex = wordStartIndex;
        int idx = 0;
        for ( int i = wordStartIndex; i < ( wordStartIndex + wordLength ) && i < lineLength; i++ ) {
            if ( sub[idx] == string[i] ) {
                contains = true;
                checkEndIndex++;
                idx++;
            } else {
                contains = false;
                break;
            }
        }
    }
    // return false if does not contains
    if ( checkEndIndex - wordStartIndex != wordLength ) {
        return false;
    }

    // performing other checks if substring exists
    int wordEndIndex = wordStartIndex + wordLength - 1;
    if ( wordStartIndex == 0 ) {
        if ( wordEndIndex + 1 == lineLength ) {
            return contains;
        }
        if ( wordEndIndex + 1 < lineLength && !isAlpha( string[wordEndIndex + 1] ) ) {
            return contains;
        }
    } else {
        if ( wordEndIndex + 1 == lineLength && !isAlpha( string[wordStartIndex - 1] ) ) {
            return contains;
        } else if ( wordEndIndex + 1 < lineLength) {
            char before = string[wordStartIndex - 1];
            char after = string[wordEndIndex + 1];
            if ( !isAlpha( before ) && !isAlpha( after ) ) {
                return contains;
            }
        }
    }
    contains = false;
    if (wordEndIndex + wordLength < lineLength - 1) {
        wordStartIndex = wordEndIndex + 1;
        goto startCheck;
    }
    return contains;
}
