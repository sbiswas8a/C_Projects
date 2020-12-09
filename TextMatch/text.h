/** @file text.h
 * @author Sumit Biswas
 * Header file for the 'Text' component of the program
 */

 #include <stdio.h>
 #include <stdlib.h>

/** Constant for maximum number of lines that can be read */
 #define MAX_LINES 10000
 /** Constant for maximum number of characters a line can have */
 #define MAX_CHARS 80

/** Opens the text file with the given name and reads the file's
 * contents into arrays of strings.
 * @param filename is the name of the file to be read
 */
void readText ( char const filename[] );

/** Returns the number of lines that were read form the input files
 * @return returns the number of lines
 */
int lineCount();

/** Returns the text in line i of the input file.
 * @param idx is the line number specified
 * @return returns the line of text from the line number passed in
 */
char const *getLine( int idx );
