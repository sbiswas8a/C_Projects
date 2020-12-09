/** @file select.c
 * @author Sumit Biswas
 * Program that lets you select and view specific lines from the input files
 */

#include "match.h"
#include "text.h"

/** Minimum number of arguments required for a valid execution */
#define MIN_ARGS 2
/** Constant used to add to index of array being traversed */
#define PLUS_THREE 3
/** Constant used to add to index of array being traversed */
#define PLUS_TWO 2
/** Divisor used when calculating required field width for printing */
#define DIVISOR 10

/** Function called when incorrect usage of the program is detected
 * Prints error message for usage and terminates program
 */
static void error() {
    fprintf( stderr, "usage: select ( [-lines <start> <end>]\n" );
    fprintf( stderr, "                [+lines <start> <end>]\n" );
    fprintf( stderr, "                [-pat <string>]\n" );
    fprintf( stderr, "                [+pat <string>]\n" );
    fprintf( stderr, "                [-word <string>]\n" );
    fprintf( stderr, "                [+word <string>] )* <text-file>\n" );
    exit( EXIT_FAILURE );
}

/** Function that checks if a line is in the range to be included or excluded, and
 * returns if the line should be printed
 * @param check -1 if the range is to be excluded / 1 if the range is to be included
 * @param lineIdx is the index of the line being checked
 * @param argc is the number of arguments passed with program execution
 * @param argIdx is the index from where the range numbers will be specified
 * @param argv is the array of arguments passed in
 */
static bool rangeMod( int check, int lineIdx, int argc, int argIdx, char *argv[] ) {
    if ( argIdx + MIN_ARGS >= argc ) {
        error();
    }
    if ( check == 1 ) {
        if ( inRange( lineIdx, argv[argIdx + 1], argv[argIdx + PLUS_TWO] ) ) {
            return true;
        } else {
            return false;
        }
    } else if ( check == -1 ) {
        if ( inRange( lineIdx, argv[argIdx + 1], argv[argIdx + PLUS_TWO] ) ) {
            return false;
        }
    }
    return true;
}

/** Function that checks if a word is to be excluded from the search or included, and
 * returns if the line should be printed
 * @param check -1 if the word is to be excluded / 1 if the word is to be included
 * @param lineIdx is the index of the line being checked
 * @param argc is the number of arguments passed with program execution
 * @param argIdx is the index from where the word will be specified
 * @param argv is the array of arguments passed in
 */
static bool wordMod( int check, int lineIdx, int argc, int argIdx, char *argv[] ) {
    if ( argIdx + 1 >= argc ) {
        error();
    }
    if ( check == 1 ) {
        if ( containsWord( getLine( lineIdx ), argv[argIdx + 1] ) ) {
            return true;
        } else {
            return false;
        }
    } else if ( check == -1 ) {
        if ( containsWord( getLine( lineIdx ), argv[argIdx + 1] ) ) {
            return false;
        }
    }
    return true;
}

/** Function that checks if a pattern is to be excluded from the search or included, and
 * returns if the line should be printed
 * @param check -1 if the pattern is to be excluded / 1 if the pattern is to be included
 * @param lineIdx is the index of the line being checked
 * @param argc is the number of arguments passed with program execution
 * @param argIdx is the index from where the pattern will be specified
 * @param argv is the array of arguments passed in
 */
static bool patMod( int check, int lineIdx, int argc, int argIdx, char *argv[] ) {
    if ( argIdx + 1 >= argc ) {
        error();
    }
    if ( check == 1 ) {
        if ( containsPattern( getLine( lineIdx ), argv[argIdx + 1] ) ) {
            return true;
        } else {
            return false;
        }
    } else if ( check == -1 ) {
        if ( containsPattern( getLine( lineIdx ), argv[argIdx + 1] ) ) {
            return false;
        }
    }
    return true;
}

/** Starts the Program
 * @param argc is the number of arguments passed #include
 * @param argv is the 2D array of the arguments
 * @return returns the exit status
 */
int main( int argc, char *argv[] )
{
    if ( argc < MIN_ARGS ) {
        error();
    }

    char toPrint[MAX_LINES][MAX_CHARS + 1];
    int toPrintNum[MAX_LINES];
    int printIdx = 0;
    char *plusWord = "+word";
    char *minusWord = "-word";
    char *plusPat = "+pat";
    char *minusPat = "-pat";
    char *plusLines = "+lines";
    char *minusLines = "-lines";

    //////////////////////////// booleans
    bool selectionMade = false;
    bool includeString = false;
    bool excludeString = false;
    bool lineIncluded = false;
    bool lineExcluded = false;

    // reading in text from file
    readText( argv[argc - 1] );

    for ( int i = 0; i < lineCount(); i++ ) { // <<--xx

        selectionMade = false;
        includeString = false;
        excludeString = false;
        lineExcluded = false;
        lineIncluded = false;

        // looping for each argument
        int j = 1;
        while ( j < argc - 1 ) { // <<--oo
            if ( strcmp( argv[j], plusLines ) == 0 ) {
                if ( !lineIncluded ) {
                    lineIncluded = rangeMod( 1, i, argc - 1, j, argv );
                }
                if ( lineIncluded && lineExcluded ) {
                    if ( rangeMod( 1, i, argc - 1, j, argv ) ) {
                        lineExcluded = false;
                    }
                }
                j += PLUS_THREE;
            } else if ( strcmp( argv[j], minusLines ) == 0 ) {
                if ( !lineExcluded ) {
                    lineExcluded = !( rangeMod( -1, i, argc - 1, j, argv ) );
                }
                if ( lineIncluded && lineExcluded ) {
                    if ( !rangeMod( -1, i, argc - 1, j, argv ) ) {
                        lineIncluded = false;
                    }
                }
                j += PLUS_THREE;
            } else if ( strcmp( argv[j], plusWord ) == 0 ) {
                if ( !includeString ) {
                    includeString = wordMod( 1, i, argc - 1, j, argv );
                }
                if ( includeString && excludeString ) {
                    if ( wordMod( 1, i, argc - 1, j, argv ) ) {
                        excludeString = false;
                    }
                }
                selectionMade = true;
                j += PLUS_TWO;
            } else if ( strcmp( argv[j], minusWord ) == 0 ) {
                if ( !excludeString ) {
                    excludeString = !( wordMod( -1, i, argc - 1, j, argv ) );
                }
                if ( includeString && excludeString ) {
                    if ( !wordMod( -1, i, argc - 1, j, argv ) ) {
                        includeString = false;
                    }
                }
                selectionMade = true;
                j += PLUS_TWO;
            } else if ( strcmp( argv[j], plusPat ) == 0 ) {
                if ( !includeString ) {
                    includeString = patMod( 1, i, argc - 1, j, argv );
                }
                if ( includeString && excludeString ) {
                    if ( patMod( 1, i, argc - 1, j, argv ) ) {
                        excludeString = false;
                    }
                }
                selectionMade = true;
                j += PLUS_TWO;
            } else if ( strcmp( argv[j], minusPat ) == 0 ) {
                if ( !excludeString ) {
                    excludeString = !( patMod( -1, i, argc - 1, j, argv ) );
                }
                if ( includeString && excludeString ) {
                    if ( !patMod( -1, i, argc - 1, j, argv ) ) {
                        includeString = false;
                    }
                }
                selectionMade = true;
                j += PLUS_TWO;
            } else {
                // print usage message
                error();
            }
        } // <<--oo

        ///////// add to array for printing
        if ( !selectionMade ) {
            if ( lineIncluded && !lineExcluded ) {
                strcpy( toPrint[printIdx], getLine(i) );
                toPrintNum[printIdx] = i + 1;
                printIdx++;
            }
        } else {
            if ( !lineIncluded && !lineExcluded ) {
                if ( includeString && !excludeString ) {
                    strcpy( toPrint[printIdx], getLine(i) );
                    toPrintNum[printIdx] = i + 1;
                    printIdx++;
                }
            } else {
                if ( lineIncluded && !lineExcluded ) {
                    if ( includeString && !excludeString ) {
                        strcpy( toPrint[printIdx], getLine(i) );
                        toPrintNum[printIdx] = i + 1;
                        printIdx++;
                    } else if ( !includeString && !excludeString ) {
                        strcpy( toPrint[printIdx], getLine(i) );
                        toPrintNum[printIdx] = i + 1;
                        printIdx++;
                    }
                }
            }
        }
    } // <<--xx

    // determining field width
    int width = 1;
    int numLines = lineCount();
    while ( numLines >= DIVISOR ) {
        numLines /= DIVISOR;
        width++;
    }
    // printing stuff
    for ( int i = 0; i < printIdx; i++ ) {
        printf("%*d %s\n", width, toPrintNum[i], toPrint[i] );
    }

    return EXIT_SUCCESS;
}
