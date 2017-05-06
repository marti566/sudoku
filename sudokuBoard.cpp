#ifndef BOARD_H
#define BOARD_H

#include "sudokuCell.h"
#include "sudokuBoard.h"
using namespace std;

Board::board()
{
//doesn't need to do anything
}

Board::board(int board[81])
{

	for(int i = 0; i < 81; i++)
	{
		if(board[81] != 0)
		{
			cells[i].setDigit(board[i]);
		}
	}
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
}
#endif