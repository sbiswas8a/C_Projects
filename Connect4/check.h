/** @file check.h
 * @author Sumit Biswas
 * Header file for check component
 */

#include <stdbool.h>

/**
 * Number of discs needed in a horizontal / vertical / diagonal line to win the game
 */
#define N 4

/**
 * Function that checks if there is a winner
 * @param rows is the number of rows in the Board
 * @param cols is the number of columns in the board
 * @param board is the board being checked for a winner
 * @param color is the color of the last disc added
 * @param row is the index of the row where the last disc was added
 * @param col is the index of the col where the last disc was added
 * @return returns true if there is a winner, false, otherwise
 */
bool checkForWinner(int rows, int cols, char board[rows][cols], char color, int row, int col);

/**
 * Function that checks if the board is full
 * @param rows is the number of rows in the Board
 * @param cols is the number of columns in the board
 * @param board is the board being checked
 * @return returns true if the board is full, false, otherwise
 */
bool checkIfFull(int rows, int cols, char board[rows][cols]);
