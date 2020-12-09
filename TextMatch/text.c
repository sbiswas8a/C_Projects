/** @file text.c
 * @author Sumit Biswas
 * Text component of the program that reads and stores the contents of
 * the input file
 */

#include "text.h"

/** Global variable for multi-dimensional array of chars */
static char lines[MAX_LINES][MAX_CHARS + 1];
/** Global variable for line count */
static int numLines = 1;

void readText( char const filename[] )
{
    int ch;
    int charCount = 0;
    int idx = 0;

    FILE *fp = fopen( filename, "r" );
    if ( !fp ) {
        fprintf( stderr, "%s%s\n", "Can't open file: ", filename );
        exit( EXIT_FAILURE );
    }
    while ( ( ch = fgetc( fp ) ) != EOF ) {
        if ( ch == '\n' ) {
            lines[idx][charCount] = '\0';
            if ( ( ch = fgetc( fp ) ) != EOF ) {
                numLines++;
                ungetc( ch, fp );
            }
            if ( numLines > MAX_LINES && ( ( ch = fgetc( fp ) ) != EOF ) ) {
                fprintf( stderr, "%s%s\n", "Too many lines: ", filename );
                fclose ( fp );
                exit( EXIT_FAILURE );
            }
            charCount = 0;
            idx++;
        } else {
            lines[idx][charCount] = ch;
            charCount++;
            if ( charCount > MAX_CHARS) {
                fprintf( stderr, "%s%s%s%d\n", "Line too long: ", filename, ":", numLines );
                fclose ( fp );
                exit( EXIT_FAILURE );
            }
        }
    }
    fclose ( fp );
}

int lineCount()
{
    return numLines;
}

char const *getLine( int idx )
{
    if ( idx < 0 ) {
        fprintf( stderr, "Invalid line number: %d\n", idx );
        exit( EXIT_FAILURE );
    }
    return lines[idx];
}
