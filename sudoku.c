/*
* Sudoku solver v1.1
* @Author: Freezing
* @Date: 03/02/2020
*/

#include <stdio.h>
#include <stdlib.h> 

#define MAX_COLS 9
#define MAX_ROWS 9

#define FILE_INPUT "sudoku_in.txt"
#define FILE_OUTPUT "sudoku_out.txt"

#define FILE_ERROR 1
#define INPUT_ERROR 2

/*
* Reads input from file
*/
int readInput ( char sudoku_board [MAX_ROWS][MAX_COLS], FILE * fs, int * filledNumbers )
{
    int err;
    int row = 0;
    int col = 0;
    char c;
    while ( row < MAX_ROWS )
    {
        if ( (err = fscanf (fs, "%c", &c)) != 1 || ( ( c < '1' || c > '9' ) && c != '\n' && c != '*' ) )
        {
            if ( err == EOF ) {
                break;
            } else {
                return 0;
            }
        }         
        if ( col == MAX_COLS )
        {
            if ( c != '\n' ) {
                return 0;
            }
            col = 0;
            row++;
        }
        else
        {
            if ( c == '\n' ) {
                return 0;
            }
            if ( c >= '1' && c <= '9' ) {
                (*filledNumbers)++;
            }
            sudoku_board [row] [col] = c;
            col++;
        }
    }
    if ( ( row < MAX_ROWS && col != MAX_COLS ) || ( row == MAX_ROWS && col != 0 ) ) {
        return 0;
    }
    return 1;
}
/*
* Prints out sudoku board
*/
void printBoard ( char sudoku_board [MAX_ROWS][MAX_COLS], FILE * fw )
{
    int j = 0;
    for ( int i = 0; i < MAX_ROWS; i ++ )
    {
        if ( i % 3 == 0 ) {
            fprintf ( fw, "+==========================+\n" );
            printf ( "+==========================+\n" );
        }
        for ( ; j < MAX_COLS; j++ )
        {
            if ( j == 0 ) {
                fprintf ( fw, "| " );
                printf ( "| " );
            } else if ( j % 3 == 0 ) {
                fprintf ( fw, " | " );
                printf ( " | " );
            }
            fprintf ( fw, "%c ", sudoku_board [i] [j] );
            printf ( "%c ", sudoku_board [i] [j] );
            if ( j == 8 ) {
                fprintf ( fw, " | " );
                printf ( " | " );
            }
        }
        if ( i == 8 ) {
            fprintf ( fw, "\n+==========================+\n" );
            printf ( "\n+==========================+\n" );
        } else {
            fprintf ( fw, "\n" );
            printf ( "\n" );
        }
        j = 0;
    }
}
/*
* Horizontal check
*/
int isInRow ( char sudoku_board [MAX_ROWS][MAX_COLS], int row, int col, int number, int validityCheck )
{
	for ( int i = 0; i < MAX_ROWS; i++ )
	{
		if ( sudoku_board [row] [i] == number + '0' ) {
            if ( validityCheck == 1 && col == i ) {
                continue;
            } else {
			    return 1;
            }
		}
	}
	return 0;
}
/*
* Vertical check
*/
int isInCol ( char sudoku_board [MAX_ROWS][MAX_COLS], int row, int col, int number, int validityCheck )
{
	for ( int i = 0; i < MAX_COLS; i++ )
	{
		if ( sudoku_board [i] [col] == number + '0' ) {
            if ( validityCheck == 1 && row == i ) {
                continue;
            } else {
			    return 1;
            }
		}
	}
	return 0;
}
/*
* Box check
*/
int isInBox ( char sudoku_board [MAX_ROWS][MAX_COLS], int row, int col, int n, int validityCheck )
{
    int r = row - row % 3;
    int c = col - col % 3;
    for ( int i = r; i < r + 3; i++ )
    {
        for ( int j = c; j < c + 3; j++ )
        {
            if ( sudoku_board [i] [j] == n + '0' ) {
                if ( validityCheck == 1 && row == i && col == j ) {
                    continue;
                } else {
			        return 1;
                }
            }
        }
    } 
    return 0;
}
/*
* Checks if given number could be filled into desired slot or not
*/
int isAllowed ( char sudoku_board [MAX_ROWS][MAX_COLS], int row, int col, int n, int validityCheck )
{
    return ! ( isInRow ( sudoku_board, row, col, n, validityCheck ) 
            || isInCol ( sudoku_board, row, col, n, validityCheck ) 
            || isInBox ( sudoku_board, row, col, n, validityCheck ) );
}
/*
* Recursive function to find actual sudoku solution
*/
int sudokuRec ( char sudoku_board [MAX_ROWS][MAX_COLS] )
{
	for ( int row = 0; row < MAX_ROWS; row++ )
	{
		for ( int col = 0; col < MAX_COLS; col++ )
		{
			if ( sudoku_board [row] [col] == '*' )
			{
				for ( int number = 1; number <= 9; number++ )
				{			       
					if ( isAllowed ( sudoku_board, row, col, number, 0 ) )
					{	
						sudoku_board [row] [col] = number + '0';
						if ( sudokuRec ( sudoku_board  ) ) {			     
							return 1;
						}
						else {			        
						    sudoku_board [row] [col] = '*';
						}
					}
				}
				return 0;
			}
		}
	}
	return 1;
}
/*
* Checks given sudoku board if it's solvable or not (looking for duplicit numbers in row, column or box)
*/
int isValidSudoku ( char sudoku_board [MAX_ROWS][MAX_COLS] )
{
    int j = 0;
    char num;
    for ( int i = 0; i < MAX_ROWS; i++ )
    {
        for ( ; j < MAX_COLS; j++ )
        {
            if ( sudoku_board [i] [j] != '*' )
            {
                num = sudoku_board [i] [j];
                if ( ! isAllowed (sudoku_board, i, j, num - '0', 1 ) ) {
                    return 0;
                }
            }
        }
        j = 0;
    }
    return 1;
}
/*
* Wrapper function for solving the sudoku
*/
int solveSudoku ( char sudoku_board [MAX_ROWS][MAX_COLS] )
{
    if ( ! isValidSudoku ( sudoku_board ) || ! sudokuRec ( sudoku_board ) ) {
        return 0;
    }
    return 1;
}
/*
* Opening files
*/
void openFiles ( FILE ** fs, FILE ** fw, int * flag )
{
    if ( ! ((*fs) = fopen (FILE_INPUT, "r")) ) { 
        printf ( "File containing sudoku %s could not be opened!\n", FILE_INPUT );
        (*flag)++;
    }
    if ( ! ((*fw) = fopen (FILE_OUTPUT, "w")) ) 
    { 
        printf ( "The file %s, where the solved sudoku is to be written, could not be opened!\n", FILE_OUTPUT );
        if ( fclose(*fs) != 0 ) {
            printf ( "Error while closing file%s\n", FILE_INPUT );  
        }
        (*flag)++;
    }
}
/*
* Closing files
*/
void closeFiles ( FILE * fs, FILE * fw )
{
    if ( fclose(fs) != 0 ) {
        printf ( "Error while closing file %s\n", FILE_INPUT );
    }
    if ( fclose(fw) != 0 ) {
        printf ( "Error while closing file %s\n", FILE_OUTPUT );
    }
}

/* Main */
int main()
{
    char sudoku_board [MAX_ROWS] [MAX_COLS];
    FILE * fs,
         * fw;
    int filledNumbers = 0;
    int flag = 0;

    openFiles ( &fs, &fw, &flag );
    if ( flag != 0 ) {
        return FILE_ERROR;
    }

    printf ( "Insert sudoku:\n" );
    if ( ! (readInput ( sudoku_board, fs, &filledNumbers )) )
    {
        printf ( "Wrong input - forbidden characters or input is shorter/longer that it should be.\n" );
        return INPUT_ERROR;
    }

    fprintf ( fw, "Given sudoku:\n" );
    printf ( "Given sudoku:\n" );
    printBoard ( sudoku_board, fw );
    fprintf ( fw, "___________________________________\nSolved sudoku:\n___________________________________\n" );
    printf ( "___________________________________\nSolved sudoku:\n___________________________________\n" );
    if ( ! solveSudoku ( sudoku_board ) ) {
        fprintf ( fw, "Solution does not exist.\n" );
        printf ( "Solution does not exist.\n" );
    }
    else
    {
        if ( filledNumbers < 17 ) {
            fprintf ( fw, "Sudoku could have more solutions, this is one of them:\n" );
            printf ( "Sudoku could have more solutions, this is one of them:\n" );
        }
        printBoard ( sudoku_board, fw );
    }

    closeFiles ( fs, fw );
    return 0;
}
