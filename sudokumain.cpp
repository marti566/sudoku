#include <iostream>
#include <fstream>
#include "sudokuCell.h"
#include "sudokuBoard.h"
#include "sudokuVariable.h"
#include <cstdlib>
#include <ctime> 
#include <fstream>

Board CSPRecursion(Board, bool& found);
Board constraintSatisfaction(Board currentBoard);

void destroy(Variable*);
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
	Variable* TempVar;
	TempVar = board.getMostConstrainedList();
	
}

Board constraintSatisfactionStart(Board currentBoard)
{
	int newBoard[81];
	bool found = false;
	if(true)
	{
		Variable* MCLRoot;
		Variable* LCLRoot;
		MCLRoot = currentBoard.getMostConstrainedList();
		while(MCLRoot != NULL)
		{
			LCLRoot = currentBoard.getLeastConstrainingList(MCLRoot);
			while(LCLRoot != NULL)
			{

				if(currentBoard.forwardChecking(LCLRoot))
				{
					currentBoard.getNewBoard(LCLRoot, newBoard);
					Board updatedBoard(newBoard);
					Board finalBoard = CSPRecursion(updatedBoard, found);
					if(found)
					{
						destroy(LCLRoot);
						destroy(MCLRoot);
						return finalBoard;
					}
				}
				LCLRoot = LCLRoot->getNext();
			}
			
			MCLRoot = MCLRoot->getNext();
		}
	}
	cout << "A solution wasn't found" << endl;
}
Board CSPRecursion(Board currentBoard, bool& found)
{
	int newBoard[81];
	if(found == true || currentBoard.isFinished())
	{
		found = true;
		return currentBoard;
	}
		
	else
	{
		Variable* MCLRoot;
		Variable* LCLRoot;
		MCLRoot = currentBoard.getMostConstrainedList();
		while(MCLRoot != NULL)
		{
			LCLRoot = currentBoard.getLeastConstrainingList(MCLRoot);
			while(LCLRoot != NULL)
			{

				if(currentBoard.forwardChecking(LCLRoot))
				{
					currentBoard.getNewBoard(LCLRoot, newBoard);
					Board updatedBoard(newBoard);
					Board finalBoard = CSPRecursion(updatedBoard, found);
					if(found)
					{
						destroy(LCLRoot);
						destroy(MCLRoot);
						return finalBoard;
					}
				}
				LCLRoot = LCLRoot->getNext();
			}

			MCLRoot = MCLRoot->getNext();
		}
	}
}

void destroy(Variable* element)
{
	Variable* f = element;
	Variable* b = element->getPrev();
	while(f != NULL)
	{
		f = f->getNext();
		delete f->getPrev();
	}
	while(b != NULL)
		b = b->getPrev();
	delete b->getNext();
}