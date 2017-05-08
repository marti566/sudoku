
#include "sudokuCell.h"
#include "sudokuBoard.h"
#include "sudokuVariable.h"
#include <iostream> 
#include <cstddef>
using namespace std;

Board::Board()
{
//doesn't need to do anything
}

Board::Board(int board[81])
{
	finished = false;
	//setting the board values and any domains that are empty becasue of assignment
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
	//setting the rest of the domains to reflect what they should be
	int currentX, currentY, currentSqX, currentSqY, currentDigit, currentNumbInDomain = 0;
	int offsetX, offsetY = 0;

	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			cells[j][i].getDigit(currentDigit);
			if(currentDigit != 0)
			{
				cells[j][i].getLocation(currentX, currentY, currentSqX, currentSqY);
				for(int m = 0; m < 9; m++) //for peers along the x axis
				{
					cells[m][currentY].getDomain(emptyDomain);
					if(emptyDomain[currentDigit-1] == 1)
					{
						emptyDomain[currentDigit-1] = 0;
					}
					cells[m][currentY].setDomain(emptyDomain);
				}

				for(int m = 0; m < 9; m++) //for peers along the y axis
				{
					cells[currentX][m].getDomain(emptyDomain);
					if(emptyDomain[currentDigit-1] == 1)
					{
						emptyDomain[currentDigit-1] = 0;
					}
					cells[currentX][m].setDomain(emptyDomain);
				}

				offsetX = currentSqX * 3;
				offsetY = currentSqY * 3;
				for(int m = 0; m < 3; m++) //for peers in the square
				{
					for(int n = 0; n < 3; n++)
					{
						cells[offsetX + n][offsetY + m].getDomain(emptyDomain);
						if(emptyDomain[currentDigit-1] == 1)
						{
							emptyDomain[currentDigit-1] = 0;
						}
						cells[offsetX + n][offsetY + m].setDomain(emptyDomain);
					}
				}
			}
		}
	}
	

}


Variable* Board::getMostConstrainedList()
{
	Variable* makerPtr = NULL;
	Variable* sortPtr = NULL;
	Variable* sortPtr2 = NULL;
	Variable* rootPtr = NULL;
	Variable* debugPtr = NULL;
	int digit = 0;
	int constrained = 0;
	int domain[9];
	int debugCount = 0;
	int debugX, debugY = 0;
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			cells[j][i].getDigit(digit);
			if(digit == 0)
			{
				
				makerPtr = new Variable;
				if(rootPtr == NULL && makerPtr != NULL)
				{
					//cout << "how many Times do we assing rootPtr" << endl;
					rootPtr = makerPtr;
				}
				cells[j][i].getDomain(domain);
				for(int m = 0; m < 9; m++)
				{
					if(domain[m] == 1)
						constrained++;
				}
				makerPtr->setConstrained(constrained);
				constrained = 0;

				makerPtr->setXY(j, i);
				sortPtr = rootPtr;
				if(sortPtr == makerPtr)
					continue;
				while(sortPtr != NULL)
				{

					if(makerPtr->getConstrained() >= sortPtr->getConstrained())
					{
						//cout << "in greater" << endl;
						if(sortPtr->getNext() != NULL)
							sortPtr = sortPtr->getNext();
						else
						{
							sortPtr->setNext(makerPtr);
							makerPtr->setPrev(sortPtr);
							break;
						}

						//cout << sortPtr->getConstrained() <<  endl;//TEMPORARY REMOVE 
					}
					else if(makerPtr->getConstrained() < sortPtr -> getConstrained())
					{
						//cout << "in less" << endl; 
						if(sortPtr->getPrev() == NULL && sortPtr->getNext() == NULL)
						{
							sortPtr->setPrev(makerPtr);
							makerPtr->setNext(sortPtr);
							rootPtr = makerPtr;
							break;
						}
						else if(sortPtr->getPrev() == NULL && sortPtr->getNext() != NULL)
						{
							sortPtr->setPrev(makerPtr);
							makerPtr->setNext(sortPtr);
							rootPtr = makerPtr;
							break;
						}
						else if(sortPtr->getPrev() != NULL && sortPtr->getNext() == NULL)
						{
							sortPtr2 = sortPtr->getPrev();
							sortPtr2->setNext(makerPtr);
							makerPtr->setNext(sortPtr);
							sortPtr->setPrev(makerPtr);
							makerPtr->setPrev(sortPtr2);
							break; 
						}
						else if(sortPtr->getPrev() != NULL && sortPtr->getNext() != NULL)
						{
							sortPtr2 = sortPtr->getPrev();
							sortPtr2->setNext(makerPtr);
							makerPtr->setNext(sortPtr);
							sortPtr->setPrev(makerPtr);
							makerPtr->setPrev(sortPtr2);
							break;
						}
					}
				}
			}
		}
	}
	int x, y = 0;
	sortPtr = rootPtr;
	while(sortPtr != NULL)
	{
		sortPtr->getXY(x, y);
		sortPtr->getValue(digit);
		cout << "X: "<< x << " Y: " << y << " Value: " << digit << " Constrained: " << sortPtr->getConstrained() << endl;
		sortPtr = sortPtr ->getNext();	
	}
	return rootPtr;

}
Variable* Board::getLeastConstrainingList(Variable* MCLVar)
{
	int x, y,digit = 0;
	int domain[9];
	int tempDomain[9];
	int constrained[9];
	for(int i = 0; i < 9; i++)
	{
		constrained[i] = 0;
	}
	MCLVar->getXY(x, y);
	cells[x][y].getDomain(domain);
	for(int i = 0; i < 9; i++)
	{
		cells[x][i].getDomain(tempDomain);
		for(int j = 0; j < 9; j++)
		{
			if(tempDomain[j] == 1 && i != y)
				constrained[j]++;
		}
		cells[i][y].getDomain(tempDomain);
		for(int j = 0; j < 9; j++)
		{
			if(tempDomain[j] == 1 && i != x)
				constrained[j]++;
		}

	}
	int offsetY, offsetX = 0;
	offsetX = x / 3;
	offsetY = y / 3;
	for(int i = 0; i < 3; i++)
	{

		for(int j = 0; j < 3; j++)
		{
			cells[offsetX * 3 + j][offsetY * 3 + i].getDomain(tempDomain);
			for(int m = 0; m <9; m++)
			{
				if(tempDomain[m]==1)
					constrained[m]++;
			}
		}
	}
	Variable* sortPtr = NULL;
	Variable* sortPtr2 = NULL;
	Variable* rootPtr = NULL;
	Variable* makerPtr = NULL;
	for(int i = 0; i < 9; i++)
	{
		if(domain[i] == 1)
		{
			constrained[i]--;
			makerPtr = new Variable;
			if(makerPtr != NULL && rootPtr == NULL)
				rootPtr = makerPtr;
			makerPtr->setXY(x, y);
			makerPtr->setConstrained(constrained[i]);
			makerPtr->setValue(i+1);
			sortPtr = rootPtr;
			if(sortPtr == makerPtr)
				continue;
			while(sortPtr->getNext() != NULL)
			{
				
				if(makerPtr->getConstrained() >= sortPtr->getConstrained())
				{
						//cout << "in greater" << endl;
					if(sortPtr->getNext() != NULL)
						sortPtr = sortPtr->getNext();
					else
					{
						sortPtr->setNext(makerPtr);
						makerPtr->setPrev(sortPtr);
						break;
					}

						//cout << sortPtr->getConstrained() <<  endl;//TEMPORARY REMOVE 
				}
				else if(makerPtr->getConstrained() < sortPtr -> getConstrained())
				{
						//cout << "in less" << endl; 
					if(sortPtr->getPrev() == NULL && sortPtr->getNext() == NULL)
					{
						sortPtr->setPrev(makerPtr);
						makerPtr->setNext(sortPtr);
						rootPtr = makerPtr;
						break;
					}
					else if(sortPtr->getPrev() == NULL && sortPtr->getNext() != NULL)
					{
						sortPtr->setPrev(makerPtr);
						makerPtr->setNext(sortPtr);
						rootPtr = makerPtr;
						break;
					}
					else if(sortPtr->getPrev() != NULL && sortPtr->getNext() == NULL)
					{
						sortPtr2 = sortPtr->getPrev();
						sortPtr2->setNext(makerPtr);
						makerPtr->setNext(sortPtr);
						sortPtr->setPrev(makerPtr);
						makerPtr->setPrev(sortPtr2);
						break; 
					}
					else if(sortPtr->getPrev() != NULL && sortPtr->getNext() != NULL)
					{
						sortPtr2 = sortPtr->getPrev();
						sortPtr2->setNext(makerPtr);
						makerPtr->setNext(sortPtr);
						sortPtr->setPrev(makerPtr);
						makerPtr->setPrev(sortPtr2);
						break;
					}
				}
			}

		}

	}
	sortPtr = rootPtr;
	while(sortPtr != NULL)
	{
		sortPtr->getXY(x, y);
		sortPtr->getValue(digit);
		cout << "X: "<< x << "Y: " << y << "Value: " << digit << "Constrained: " << sortPtr->getConstrained() << endl;
		sortPtr = sortPtr ->getNext();	
	}


	return rootPtr;

}
bool Board::forwardChecking(Variable* LCLVar)
{


}
void Board::getNewBoard(Variable* NextMove, int newBoard[81])
{

}
bool Board::isFinished()
{
	int digit = 0;
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			cells[j][i].getDigit(digit);
			if(digit ==  0)
				return false;
		}
	}
	int digitsX[9];
	int digitsY[9];
	int count = 0;
	for(int i = 0; i < 9; i++)
	{
		digitsX[i] = 1;
		digitsY[i] = 1;
	}
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			cells[j][i].getDigit(digit);
			if(digitsX[digit-1] == 0)
				return false;
			else
				digitsX[digit-1] = 0;
			cells[i][j].getDigit(digit);
			if(digitsY[digit-1] == 0)
				return false;
			else
				digitsY[digit-1] = 0;
		}
		for(int n = 0; n < 9; n++)
		{
			if(digitsX[n] == 1 || digitsY[n] == 1)
				return false;
			else
			{
				digitsX[n] = 1;
				digitsY[n] = 1;
			}

		}

	}
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			for(int m = 0; m < 3; m++)
			{
				for(int n = 0; n < 3; n++)
				{
					cells[j*3+n][i*3+m].getDigit(digit);
					if(digitsX[digit-1] == 0)
						return false;
					else
						digitsX[digit-1] = 0;
				}
			}
			for(int m = 0; m < 9; m++)
			{
				if(digitsX[m] == 1)
					return false;
				else
					digitsX[m] = 1;
			}
		}
	}
	return true;
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