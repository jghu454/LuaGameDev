#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

const int size_of_game = 10;
//slot 0 is the actual print while slot 1 is the hidden values that determine what cell will print out
//e = empty but will print out an "o" if untriggered or a number/"x" if triggered
//b = bomb but if triggered will print out "*"
//f = flag but will print out an "F"

char board[size_of_game][size_of_game][2]; 

bool activeGame = true;
int bombs = 10;




char getCell(int row, int column, int slot)
{
	return board[row][column][slot];
}


void setCell(int row, int column, int slot,  char value)
{
	board[row][column][slot] = value;
}

void printBoard()
{
	cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
	cout << "  ___________________" << endl;

	for (int rows = 0; rows < size_of_game; rows++)
	{
		cout << rows << "|";
		for (int columns = 0; columns < size_of_game; columns++)
		{
			cout << getCell(rows, columns, 1)<<" ";
		}
		cout << endl;
	}
}

char aToI(int x)
{
	switch (x)
	{
	case 0:
		return 'x';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5: 
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	}
}
void setupBoard()
{
	//Set entire board to nothing first
	for (int rows = 0; rows < size_of_game; rows++)
	{
		for (int columns = 0; columns < size_of_game; columns++)
		{
			setCell(rows, columns,0, 'o');
			setCell(rows, columns, 1, 'e');
			
		}
	}

	//set bombs
	int placedBombs = 0;
	while (placedBombs < bombs)
	{
		int bomb_row = rand() % 10;
		int bomb_column = rand() % 10;

		if (getCell(bomb_row, bomb_column, 1) != 'b')
		{
			placedBombs++;
			setCell(bomb_row, bomb_column, 1, 'b');
		}
		
	}
}
int checkAround(int r, int c)
{
	int start_r = r - 1;
	int start_c = c - 1;
	int end_r = r + 1;
	int end_c = c + 1;

	if (r == 0)
	{
		start_r = 0;
	}
	else if (r >= 9)
	{
		end_r = 9;
	}

	if (c == 0)
	{
		start_c = 0;
	}
	else if (c >= 9)
	{
		end_c = 9;
	}

	int bomb_count = 0;

	for (int row = start_r; row <= end_r; row++)
	{
		for (int column = start_c; column <= end_c; column++)
		{
			
			if (getCell(row, column, 1) == 'b')
			{
				
				bomb_count++;
			}
		}
	}

	return bomb_count;
}
void reveal(int r, int c)
{
	if (getCell(r, c, 1) == 'b')
	{
		activeGame = false;
	}
	
	if (checkAround(r, c) != 0)
	{
		int x = checkAround(r, c);
		setCell(r, c, 0, aToI(x));
	}
	else {
		
		int x = checkAround(r, c);
		setCell(r, c, 0, aToI(x));

		int start_r = r - 1;
		int start_c = c - 1;
		int end_r = r + 1;
		int end_c = c + 1;

		if (r == 0)
		{
			start_r = 0;
		}
		else if (r >= 9)
		{
			end_r = 9;
		}

		if (c == 0)
		{
			start_c = 0;
		}
		else if (c >= 9)
		{
			end_c = 9;
		}

		int bomb_count = 0;

		for (int row = start_r; row <= end_r; row++)
		{
			for (int column = start_c; column <= end_c; column++)
			{

				if (getCell(row, column, 0) == 'o' && getCell(row, column, 1) != 'b')
				{
					reveal(row, column);
				}
			}
		}
	}

	

	
}






 

int main() 
{
	cout << "MINE SWEEPER" << endl;
	setupBoard();
	printBoard();

	while (activeGame)
	{
		cout << "Enter a row: ";
		int row;
		int column;
		cin >> row;
		
		cout <<endl<< "Enter a column: ";
		cin >> column;

		reveal(row,column);
		cout << endl;
		printBoard();
	}
	cout << "Game over" << endl;
}