#include "sudokuCell.h"
#include  <vector>
using namespace std;
Cell::Cell()
{
	xLoc == 0;
	yLoc == 0;
	digit == 0; //zero represents empty
	squareNum = 0;
	for(int i = 0; i < 9; i++)
	{
		domain[i] = 1;
	}
	numbValInDomain = 9;
}

Cell::Cell(int newXLoc, int newYLoc, int newDigit, int newSquareNum)
{
	xLoc = newXLoc;
	yLoc = newYLoc;
	digit = newDigit;
	squareNum = newSquareNum;
	if(digit != 0)
	{
		for(int i = 0; i < 9; i++)
		{
			domain[i] = 0;
		}
		numbValInDomain = 0;
	}
	else
	{
		for(int i = 0; i < 9; i++)
		{
	
			domain[i] = 1;
		}
		numbValInDomain = 9;

	}
}
Cell::~Cell()
{

}

void Cell::setLocation(int newXLoc, int newYLoc)
{
	xLoc = newXLoc;
	yLoc = newYLoc;
	return;
}
void Cell::getLocation(int &currentX, int &currentY, int &currentSquareNum)
{
	currentX = xLoc;
	currentY = yLoc;
	currentSquareNum = squareNum;
	return;
}
void Cell::setDigit(int newDigit)
{
	digit = newDigit;
	for(int i = 0; i < 9; i++)
	{
		domain[i] = 0;
	}
	return;
}
void Cell::getDigit(int &currentDigit)
{
	currentDigit = digit;
	return;
}
void Cell::setDomain(int newDomain[9])
{
	for(int i =0; i < 9; i++)
	{
		domain[i] = newDomain[i];
	}
}
void Cell::getDomain(int currentDomain[9])
{
	for(int i = 0; i < 9; i++)
	{
		currentDomain[i] = domain[i];
	}

}
void Cell::setNumbValInDomain(int newNumbValInDomain)
{
	numbValInDomain = newNumbValInDomain;
}
void Cell::getNumbValInDomain(int &currentNumbvalInDomain)
{
	currentNumbvalInDomain = numbValInDomain;
}