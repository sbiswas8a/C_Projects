/**
 * @file board.c
 * @author Sumit Biswas
 * Board component for the connect4 Program
 */

#include "board.h"

void initBoard(int rows, int cols, char board[rows][cols])
{
    for ( int i = 0; i < rows; i++ ) {
        for ( int j = 0; j < cols; j++ ) {
            board[i][j] = ' ';
        }
    }
}

/** Function that finds out the highest index row in the given column that contains a whitespace
 * @param rows is the number of rows in the Board
 * @param cols is the number of columns in the Board
 * @param board is the 2D char array that is being checked
 * @param col is the given column that is to be checked
 */
static int whichRow(int rows, int cols, char board[rows][cols], int col)
{
    for ( int i = rows - 1; i >= 0; i-- ) {
        if ( board[i][col] == ' ' ) {
            return i;
        }
    }
    return -1;
}

int addDisc(int rows, int cols, char board[rows][cols], char color, int col)
{
    int rowAdded = whichRow( rows, cols, board, col );
    if ( rowAdded == -1 ) {
        printf( "%s\n", "Full column" );
        exit(FULL_COL);
    }
    board[rowAdded][col] = color;
    return rowAdded;
}

void printBoard(int rows, int cols, char board[rows][cols])
{
    putchar( '\n' );     // put newline
    for ( int i = 1; i <= cols; i++ ) {
        printf( "%s%d%c", "  ", i, ' ' );
    }
    putchar( '\n' );     // put newline
    for ( int i = 0; i < rows; i++ ) {
        putchar( '+' );     // print +
        for ( int j = 0; j < cols; j++ ) {
            printf( "---+" );     // print ---+
        }
        putchar( '\n' );     // put newline
        putchar( '|' );     // print |
        for ( int j = 0; j < cols; j++ ) {
            printf( "%c%c%c", ' ', board[i][j], ' ' );    // print content
            putchar( '|' );     // print |
        }
        putchar( '\n' );     // put newline
    }
    putchar( '+' );     // print +
    for ( int i = 0; i < cols; i++ ) {
        printf( "---+" );     // print +--+
    }
    putchar( '\n' );     // put newline
    putchar( '\n' );     // put newline
}
