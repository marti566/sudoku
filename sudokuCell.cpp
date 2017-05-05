#include "sudokuCell.h"

Cell::Cell()
{
	xloc == 0;
	yloc == 0;
	digit == 0; //zero represents empty
	squareNum = 0;
	for(int i = 0; i < 9; i++)
	{
		Domain[i] == 0;
	}
}

Cell::Cell(int newXLoc, int newYLoc, int newDigit, int newSquareNum)
{

	
}