/**
 * @file check.c
 * @author Sumit Biswas
 * Component that checks for a winner or a full board
 */

#include "check.h"

bool checkForWinner(int rows, int cols, char board[rows][cols], char color, int row, int col)
{
    int count;

    // horizontal left check
    count = 1;
    for ( int i = 1; i < N; i++ ) {
        if ( col - i >= 0 ) {
            if ( board[row][col - i] == color ) {
                count++;
            } else {
                goto right;
            }
        } else {
            goto right;
        }
    }

    // horizontal right check
    right:
    if (count >= N) {
        goto done;
    }
    for ( int i = 1; i < N; i++ ) {
        if ( col + i < cols ) {
            if ( board[row][col + i] == color ) {
                count++;
            } else {
                goto up;
            }
        } else {
            goto up;
        }
    }

    // vertical up check
    up:
    if (count >= N) {
        goto done;
    }
    count = 1;
    for ( int i = 1; i < N; i++ ) {
        if ( row - i >= 0 ) {
            if ( board[row - i][col] == color ) {
                count++;
            } else {
                goto down;
            }
        } else {
            goto down;
        }
    }

    // vertical down check
    down:
    if (count >= N) {
        goto done;
    }
    for ( int i = 1; i < N; i++ ) {
        if ( row + i < rows ) {
            if ( board[row + i][col] == color ) {
                count++;
            } else {
                goto upLeft;
            }
        } else {
            goto upLeft;
        }
    }

    // diagonal up-left check
    upLeft:
    if (count >= N) {
        goto done;
    }
    count = 1;
    for ( int i = 1; i < N; i++ ) {
        if ( row - i >= 0 && col - i >= 0 ) {
            if ( board[row - i][col - i] == color ) {
                count++;
            } else {
                goto downRight;
            }
        } else {
            goto downRight;
        }
    }

    // diagonal down-right check
    downRight:
    if (count >= N) {
        goto done;
    }
    for ( int i = 1; i < N; i++ ) {
        if ( row + i < rows && col + i < cols ) {
            if ( board[row + i][col + i] == color ) {
                count++;
            } else {
                goto upRight;
            }
        } else {
            goto upRight;
        }
    }

    // diagonal up-right check
    upRight:
    if (count >= N) {
        goto done;
    }
    count = 1;
    for ( int i = 1; i < N; i++ ) {
        if ( row - i >= 0 && col + i < cols ) {
            if ( board[row - i][col + i] == color ) {
                count++;
            } else {
                goto downLeft;
            }
        } else {
            goto downLeft;
        }
    }

    // diagonal down-left check
    downLeft:
    if (count >= N) {
        goto done;
    }
    for ( int i = 1; i < N; i++ ) {
        if ( row + i < rows && col - i >= 0 ) {
            if ( board[row + i][col - i] == color ) {
                count++;
            } else {
                goto done;
            }
        } else {
            goto done;
        }
    }

    // checks done
    done:
    return count >= N;
}

bool checkIfFull(int rows, int cols, char board[rows][cols])
{
    for ( int i = 0; i < rows; i++ ) {
        for (int j = 0; j < cols; j++ ) {
            if ( board[i][j] == ' ' ) {
                return false;
            }
        }
    }
    return true;
}
