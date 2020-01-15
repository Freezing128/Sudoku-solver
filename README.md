# Sudoku-solver
[C] Sudoku solver v1.0
Coded by Freezing 14/01/2020

Basic C program that reads 9x9 sudoku board from stdin, solves it by using recursive backtracking algorithm and prints the solution in a neat format on stdout.

Example of usage:

INPUT FILE:
3***5*78*
4*****1*3
7*8****5*
*2**48*9*
5**26**31
6***91***
*61**5*7*
***9**3**
**4*725**

PROGRAM OUTPUT:
Insert sudoku board:
Inserted sudoku:
+==========================+
| 3 * *  | * 5 *  | 7 8 *  | 
| 4 * *  | * * *  | 1 * 3  | 
| 7 * 8  | * * *  | * 5 *  | 
+==========================+
| * 2 *  | * 4 8  | * 9 *  | 
| 5 * *  | 2 6 *  | * 3 1  | 
| 6 * *  | * 9 1  | * * *  | 
+==========================+
| * 6 1  | * * 5  | * 7 *  | 
| * * *  | 9 * *  | 3 * *  | 
| * * 4  | * 7 2  | 5 * *  | 
+==========================+
___________________________________
Calculated soluton:
___________________________________
+==========================+
| 3 1 2  | 4 5 6  | 7 8 9  | 
| 4 5 6  | 7 8 9  | 1 2 3  | 
| 7 9 8  | 1 2 3  | 4 5 6  | 
+==========================+
| 1 2 3  | 5 4 8  | 6 9 7  | 
| 5 4 9  | 2 6 7  | 8 3 1  | 
| 6 8 7  | 3 9 1  | 2 4 5  | 
+==========================+
| 2 6 1  | 8 3 5  | 9 7 4  | 
| 8 7 5  | 9 1 4  | 3 6 2  | 
| 9 3 4  | 6 7 2  | 5 1 8  | 
+==========================+

Keep in mind that this code may not be optimal, it's just something I made in my free time as a practice. I'm still learning :).