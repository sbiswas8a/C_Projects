/** @file match.h
 * @author Sumit Biswas
 * Header file for the Match component of the program
 */

 #include "text.h"
 #include <stdbool.h>
 #include <string.h>

/** Checks if the given line is in the given range of lines
 * @param idx is the index of the line being checked
 * @param start is the starting number of the range of lines
 * @param end is the ending number of the range of lines
 */
bool inRange( int idx, char const *start, char const *end );

/** Given a line of text and a string, it returns if the given line
 * contains the given string as a substring
 * @param line is the line of Text
 * @param str is the string to be matched
 * @return returns true if the given string is matched, false otherwise
 */
bool containsPattern ( char const *line, char const *str );

/** Given a line of text and a word, it returns if the given line
 * contains the given word as a substring
 * @param line is the line of Text
 * @param word is the word to be matched
 * @return returns true if the given word is matched, false otherwise
 */
bool containsWord ( char const *line, char const *word );
