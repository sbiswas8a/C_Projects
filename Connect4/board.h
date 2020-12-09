/** @file board.h
 * @author Sumit Biswas
 * Header file for board component
 */

 #include <stdio.h>
 #include <stdlib.h>

/**
 * Exit status code for when an invalid number of rows or columns was input by the user
 */
#define INVALID_ROWS_COLS 100

/**
 * Exit status code for when the disc is tried to be added to an invalid column
 */
#define INVALID_COL 101

/**
 * Exit status code for when a disc is tried to be added to a full column
 */
#define FULL_COL 102

/**
 * Minimum number of rows or columns a board can have
 */
#define MIN_ROWS_COLS 4

/**
 * Maximum number of rows or columns a board can have
 */
#define MAX_ROWS_COLS 10

/**
 * Initializes the board and fills it up with spaces
 * @param rows is the number of rows in the Board
 * @param cols is the number of columns in the Board
 * @param board is the board / 2D array of chars that needs to be initialized
 */
void initBoard(int rows, int cols, char board[rows][cols]);

/**
 * Adds a disc of the given color to the given column
 * @param rows is the number of rows in the Board
 * @param cols is the number of columns in the Board
 * @param board is the board / 2D array of chars that is being manipulated
 * @param color is the color of the disc being added
 * @param col is the column to which the disc is to be added
 * @return returns the index of the row where the disc was added
 */
int addDisc(int rows, int cols, char board[rows][cols], char color, int col);

/**
 * Prints the board / 2D char array
 * @param rows is the number of rows in the Board
 * @param cols is the number of columns in the Board
 * @param board is the 2D array of chars being printed
 */
void printBoard(int rows, int cols, char board[rows][cols]);
