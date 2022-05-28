/*This program is the game connect 4. The game build for 2 players. the porpuse of the game is to make 4 of the same symbol in row/colum/diagonally*/

#define _CRT_SECURE_NO_WARNINGS
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

/*************** Board ***************/
#define ROWS 6
#define COLS 7
#define ONE 1
#define TWO 2
char board[ROWS][COLS];

/*********** Declarations ************/
/// This function initializes the game board by assigning each cell with ' ' (resulting with an empty game board).
void initBoard();
/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);
/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);
void clearScreen(); /// This function clears the screen.
void printBoard();  ///This function prints the board.
bool getInputAndPrintSymbol();  ///This function gets input from the player and print the symbol of the player where he chose
int checkEmptyCell(int colum);  ///This function recieve number of colum and return the number on the empty row
void symbolOfPlayer(int row, int colum, int count); ///This function decide what symbol belong to each player ('X' or 'O')
void clearAndPrint();  ///This function clear the screen and print again
bool countSymbolInColum();  ///This function check if the colum is full and print announcement accordingly. If the colum is full the function will get new colum input 
bool countSymbolInRow();  ///This function check if the row is full and print announcement accordingly. If the row is full the function will get new colum input 
bool countSymbolDownDiagonal();  ///This function check if the diagonal from up to down is full and print announcement accordingly. If the diagonal is full the function will get new colum input 
bool countSymbolUpDiagonal();  ///This function check if the diagonal from down to up is full and print announcement accordingly. If the diagonal is full the function will get new colum input 
bool victoryPlayer(int count);   ///This function check if one of the players win. The function prints announcement accordingly.
void checkFullColumsPlayer(int row, int colum, int count);   ///This function check if the colum where the player put the symbol is full and tell the player to choose another colum.
void checkPlayerState(int colum, int count);

/*************** Main ****************/
int main()
{
	bool win;
	initBoard();
	printBoard();
	win=getInputAndPrintSymbol();
	//clearAndPrint();
	if(win==false)
		printf("IT'S A TIE!!");
	sleep(5);
}

/********** Implementations **********/
char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}
void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}
void initBoard()
{
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}
void clearScreen()
{
	system("cls");
}
void printBoard()
{
	int i, j;
	printf(" ");
	for (i = 1; i <= COLS; i++)
		printf("    %d", i);
	printf("\n");
	for (j = 0; j < ROWS; j++)
	{
		char rowLetter = 'A';
		printf("%c", rowLetter + j);
		for (i = 1; i <= 7; i++)
			printf("    %c", getCell(i, j + 1));
		printf("\n");
	}
}
bool getInputAndPrintSymbol()
{
	bool win;
	int colum, count, k = 0;
	for (count = 0; count < 42; count++)
	{
		if (count % 2 == 0)
		{
			printf("\nPlayer number %d:\nPlease enter colum input (a number between 1-7): ", ONE);
			scanf("%d", &colum);
			checkPlayerState(colum, count);
		}
		else
		{
			printf("\nPlayer number %d:\nPlease enter colum input (a number between 1-7): ", TWO);
			scanf("%d", &colum);
			checkPlayerState(colum, count);
		}
		win=victoryPlayer(count);
		if (win == true)
			return win;
	}
	return win;
}
int checkEmptyCell(int colum)
{
	int row;
	for (row = 6; row >= 0; row--)
		if ((getCell(colum, row) != 'X') && (getCell(colum, row) != 'O'))
			return row;
	return 0;
}
void symbolOfPlayer(int row, int colum, int count)
{
	if (count % 2 == 0)
		setCell(colum, row, 'X');
	else
		setCell(colum, row, 'O');
}
void clearAndPrint()
{
	clearScreen();
	printBoard();
}
void checkFullColumsPlayer(int row, int colum, int count)
{
	while (checkEmptyCell(colum) == 0 || (colum > 7 || colum < 0))
	{
		while (colum > 7 || colum <= 0)
		{
			printf("The col you entered is not between 1-7\nPlease enter colum input (a number between 1-7): ");
			scanf("%d", &colum);
		}
		if (checkEmptyCell(colum) == 0)
		{
			printf("The col you entered is full.\nPlease enter colum input (a number between 1-7): ");
			scanf("%d", &colum);
		}
	}
	row = checkEmptyCell(colum);
	symbolOfPlayer(row, colum, count);
}
bool countSymbolInColum()
{
	int i, j;
	bool found = false;

	for (i = 1; i <= COLS; i++)
	{
		for (j = 1; j <= ROWS - 3; j++)
		{
			if (getCell(i, j) == 'X' && getCell(i, j + 1) == 'X' && getCell(i, j + 2) == 'X' && getCell(i, j + 3) == 'X')
				found = true;
			else if (getCell(i, j) == 'O' && getCell(i, j + 1) == 'O' && getCell(i, j + 2) == 'O' && getCell(i, j + 3) == 'O')
				found = true;
		}
	}
	return found;
}
bool countSymbolInRow()
{
	int i = 1, j = 1;
	bool found = false;

	for (i = 1; i <= ROWS; i++)
	{
		for (j = 1; j <= COLS; j++)
		{

			if (getCell(j, i) == 'X' && getCell(j + 1, i) == 'X' && getCell(j + 2, i) == 'X' && getCell(j + 3, i) == 'X')
				found = true;
			else if (getCell(j, i) == 'O' && getCell(j + 1, i) == 'O' && getCell(j + 2, i) == 'O' && getCell(j + 3, i) == 'O')
				found = true;
		}
	}
	return found;
}
bool countSymbolDownDiagonal()
{
	int i, j;
	bool found = false;

	for (i = 1; i <= ROWS; i++)
	{
		for (j = 1; j <= COLS - 4; j++)
		{
			if (getCell(j, i) == 'X' && getCell(j + 1, i + 1) == 'X' && getCell(j + 2, i + 2) == 'X' && getCell(j + 3, i + 3) == 'X')
				found = true;
			else if (getCell(j, i) == 'O' && getCell(j + 1, i + 1) == 'O' && getCell(j + 2, i + 2) == 'O' && getCell(j + 3, i + 3) == 'O')
				found = true;
		}
	}
	return found;
}
bool countSymbolUpDiagonal()
{
	int i, j;
	bool found = false;

	for (i = 1; i <= ROWS; i++)
	{
		for (j = 1; j <= COLS - 4; j++)
		{
			if (getCell(j, i) == 'X' && getCell(j + 1, i - 1) == 'X' && getCell(j + 2, i - 2) == 'X' && getCell(j + 3, i - 3) == 'X')
				found = true;
			else if (getCell(j, i) == 'O' && getCell(j + 1, i - 1) == 'O' && getCell(j + 2, i - 2) == 'O' && getCell(j + 3, i - 3) == 'O')
				found = true;
		}
	}
	return found;
}
bool victoryPlayer(int count)
{
	bool flag=false;
	if (countSymbolInColum())
	{
		if (count % 2 == 0)
			printf("\nPlayer number %d won", ONE);
		else
			printf("\nPlayer number %d won", TWO);
		flag = true;
	}
	else if (countSymbolInRow())
	{
		if (count % 2 == 0)
			printf("\nPlayer number %d won", ONE);
		else
			printf("\nPlayer number %d won", TWO);
		flag = true;
	}
	else if (countSymbolDownDiagonal())
	{
		if (count % 2 == 0)
			printf("\nPlayer number %d won", ONE);
		else
			printf("\nPlayer number %d won", TWO);
		flag = true;
	}
	else if (countSymbolUpDiagonal())
	{
		if (count % 2 == 0)
			printf("\nPlayer number %d won", ONE);
		else
			printf("\nPlayer number %d won", TWO);
		flag = true;
	}
	return flag;
}
void checkPlayerState(int colum, int count)
{
	int row;
	while (colum > 7 || colum <= 0)
	{
		printf("The col you entered is not between 1-7\nPlease enter colum input (a number between 1-7): ");
		scanf("%d", &colum);
	}
	row = checkEmptyCell(colum);
	checkFullColumsPlayer(row, colum, count);
	clearAndPrint();
}
