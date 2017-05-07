#include <iostream>
#include <fstream>
#include "sudokuCell.h"
#include "sudokuBoard.h"
#include <cstdlib>
#include <ctime> 
#include <fstream>

void constraintSatisfaction(Board currentBoard);
int main(int argc, char* argv[])
{
	int input = 1;
	char fInput;
	int count = 0;
	int tempBoard[81];
	int i = 0;
	ifstream fin;
	fin.open("puzzles.txt");
	while (!fin.eof())
	{
		fInput = fin.get();
		if(fInput == '\n')
		{
			count++;
			continue;
		}
		if(input == count)
		{
			tempBoard[i] = fInput - '0';
			i++;
		}
		else if(count > input)
			break;
	}
	count = 0;
	srand(time(NULL));
	// for(int i = 0; i < 81; i++)
	// {
	// 	tempBoard[i] = rand()%1000;
	// 	cout << tempBoard[i] << " ";
	// 	count++;
	// 	if(count % 9 == 0)
	// 		cout << endl;
	// }
	Board board(tempBoard);
	cout << endl;
	board.displayBoard();
	
}

void constraintSatisfaction(Board currentBoard)
{



}