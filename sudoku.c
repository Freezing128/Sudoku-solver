/*
* Sudoku solver
* @Author: Freezing
* @Date: 14/01/2020
*/
#include <stdio.h>
#include <stdlib.h> 

#define MAX_COLS 9
#define MAX_ROWS 9

#define ERROR_TOO_LONG_INPUT -1
#define ERROR_WRONG_INPUT 0
#define SUCCESSFULLY_READ_INPUT 1

typedef struct t_board 
{
    char position [MAX_ROWS] [MAX_COLS];
} board;
/*
* Reads input from stdin
*/
int readInput ( board * gameBoard )
{
    int row = 0;
    int col = 0;
    int err;
    char c;
    printf("Insert sudoku board:\n");
    while ( 42 )
    {
        if ( row > MAX_ROWS - 1 )
            return ERROR_TOO_LONG_INPUT;
        if ( ( err = scanf ( "%c", &c ) ) != 1 || 
        ( c != '1' && c != '2' &&  c != '3' && c != '4' && 
          c != '5' && c != '6' &&  c != '7' && c != '8' && 
          c != '9' && c != '*' && c != '\n' ) )
        {
            if ( feof ( stdin ) )
                break;
            return ERROR_WRONG_INPUT;
        }
        if ( col == MAX_COLS )
        {
            row++;
            col = 0;
        }
        if ( c != '\n' )
        {
            gameBoard -> position [row] [col] = c;
            col++;
        }
    }
    if ( row != MAX_ROWS - 1 || col != MAX_COLS )
      return ERROR_WRONG_INPUT;
    return SUCCESSFULLY_READ_INPUT;
}
/*
* Prints the board on stdout 
*/
void printBoard ( board gameBoard )
{
    int j = 0;
    for ( int i = 0; i < MAX_ROWS; i ++ )
    {
        if ( i % 3 == 0 )
            printf ( "+==========================+\n" );
        for ( ; j < MAX_COLS; j++ )
        {
            if ( j == 0 )
                printf ( "| " );
            else if ( j % 3 == 0 )
                printf ( " | " );
            printf ( "%c ", gameBoard . position[i][j] );
            if ( j == 8 )
                printf ( " | " );
        }
        if ( i == 8 )
            printf ( "\n+==========================+\n" );
        else
            printf ( "\n" );
        j = 0;
    }
}
/*
* Horizontal check
*/
int isInRow ( board * gameBoard, int row, int number )
{
	for ( int i = 0; i < MAX_ROWS; i++ )
	{
		if ( gameBoard -> position [row] [i] == number + '0' )
		{
			return 1;
		}
	}
	return 0;
}
/*
* Vertical check
*/
int isInCol ( board * gameBoard, int col, int number )
{
	for ( int i = 0; i < MAX_COLS; i++ )
	{
		if ( gameBoard -> position [i] [col] == number + '0' )
		{
			return 1;
		}
	}
	return 0;
}
/*
* Box check
*/
int isInBox ( board * gameBoard, int row, int col, int n )
{
    int r = row - row % 3;
    int c = col - col % 3;
    for ( int i = r; i < r + 3; i++ )
    {
        for ( int j = c; j < c + 3; j++ )
        {
            if ( gameBoard -> position [i] [j] == n + '0' )
                return 1;
        }
    }
    return 0;
}
/*
* Checks if the number could be filled into desired spot on the board or not
*/
int isAllowed ( board * gameBoard, int row, int col, int n )
{
    return ! ( isInRow ( gameBoard, row, n ) || isInCol ( gameBoard, col, n ) || isInBox ( gameBoard, row, col, n ) );
}
/*
* Recursive function used for finding the actual solution of given sudoku problem
*/
int sudoku ( board * gameBoard )
{
	for ( int row = 0; row < MAX_ROWS; row++ )
	{
		for ( int col = 0; col < MAX_COLS; col++ )
		{
			if ( gameBoard -> position [row] [col] == '*' )
			{
				for ( int number = 1; number <= 9; number++ )
				{			       
					if ( isAllowed ( gameBoard, row, col, number ) )
					{	
						gameBoard -> position [row] [col] = number + '0';
						if ( sudoku ( gameBoard ) )
						{			     
							return 1;
						}
						else
						{			        
						    gameBoard -> position [row] [col] = '*';
						}
					}
				}
				return 0;
			}
		}
	}
	return 1;
}
/* Main function */
int main()
{
    board gameBoard;
    int error = readInput ( &gameBoard );
    int numberOfResults = 0;
    if ( error == ERROR_WRONG_INPUT )
    {
        printf ( "Wrong input.\n" );
        return -1;
    }
    else if ( error == ERROR_TOO_LONG_INPUT )
    {
        printf ( "Too long input.\n" );
        return -2;
    }
    printf ( "Inserted sudoku:\n" );
    printBoard ( gameBoard );
    printf ( "___________________________________\nCalculated soluton:\n___________________________________\n" );
    if ( ! sudoku ( &gameBoard ) )
        printf ( "Solution does not exist.\n" );
    else
        printBoard ( gameBoard );
    
    return 0;
}
