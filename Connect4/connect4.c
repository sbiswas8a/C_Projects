/** @file connect4.c
  * @author Sumit Biswas
  * Program that emulates the Connect 4 game
  */

#include "board.h"
#include "check.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Starts the Program
 * @return returns the exit condition
 */
int main()
{
    int rows, columns, check, colToAdd, playerTurn, rowAdded;

    check = scanf( "%d", &rows );
    if ( check < 1 || rows < MIN_ROWS_COLS || rows > MAX_ROWS_COLS ) {
        printf("%s\n", "Invalid rows" );
        return INVALID_ROWS_COLS;
    }
    check = scanf( "%d", &columns );
    if ( check < 1 || columns < MIN_ROWS_COLS || columns > MAX_ROWS_COLS ) {
        printf("%s\n", "Invalid cols" );
        return INVALID_ROWS_COLS;
    }

    char board[rows][columns];

    initBoard( rows, columns, board );

    playerTurn = 1;
    check = scanf( "%d", &colToAdd );
    while ( check != EOF ) {
        if ( check < 1 || colToAdd > columns || colToAdd < 1 ) {
            printf("%s\n", "Invalid column" );
            exit(INVALID_COL);
        }
        colToAdd--; // decreased by 1 to represent index of column
        if ( checkIfFull( rows, columns, board ) ) {
            printBoard( rows, columns, board );
            printf( "%s\n", "Winner: Draw" );
            return EXIT_SUCCESS;
        }
        if ( playerTurn == 1 ) {
            rowAdded = addDisc( rows, columns, board, 'R', colToAdd );
            if ( checkForWinner( rows, columns, board, 'R', rowAdded, colToAdd ) ) {
                printBoard( rows, columns, board );
                printf( "%s\n", "Winner: Red" );
                return EXIT_SUCCESS;
            }
            playerTurn = 2;
        } else {
            rowAdded = addDisc( rows, columns, board, 'Y', colToAdd );
            if ( checkForWinner( rows, columns, board, 'Y', rowAdded, colToAdd  ) ) {
                printBoard( rows, columns, board );
                printf( "%s\n", "Winner: Yellow" );
                return EXIT_SUCCESS;
            }
            playerTurn = 1;
        }
        check = scanf( "%d", &colToAdd );
    }
    printBoard( rows, columns, board );
    printf( "%s\n", "Winner: None" );
    return EXIT_SUCCESS;
}
