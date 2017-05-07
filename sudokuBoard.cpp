
#include "sudokuCell.h"
#include "sudokuBoard.h"
#include <iostream> 
using namespace std;

Board::Board()
{
//doesn't need to do anything
}

Board::Board(int board[81])
{
	int tempIter;
	int tempSqX;
	int tempSqY;
	int emptyDomain[9];
	for(int i = 0; i < 9; i++)
	{
		emptyDomain[i] = 0;
	}
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			tempIter = i * 9 + j;
			tempSqX = j / 3;
			tempSqY = i / 3;
			if(board[tempIter] != 0)
			{
				cells[j][i].setDigit(board[tempIter]);
				cells[j][i].setLocation(j, i, tempSqX, tempSqY);
				cells[j][i].setDomain(emptyDomain);
			}
			else
			{
				cells[j][i].setLocation(j, i, tempSqX, tempSqY);
			}

		}
		
	}
	tempIter = 0;
	
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			cells[j][i].getDigit(&tempIter);
			if(tempIter != 0)
			{
				int currentX, currentY, currentSqX, currentSqY;
			}
		}
	}
	

}

void Board::updateBoard(int xOfChanged, int yOfChanged)
{


}
void Board::getLeastConstrained(int x, int y)
{

}
void Board::displayBoard()
{
	int tempdigit = 0;
	for(int i = 0; i < 9; i++)
	{

		for(int j = 0; j < 9; j++)
		{
			cells[j][i].getDigit(tempdigit);
			cout << tempdigit << " ";
		}
		cout << endl;
	}
}