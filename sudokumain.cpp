#include <iostream>
#include <fstream>
#include "sudokuCell.h"
#include "sudokuBoard.h"
#include "sudokuVariable.h"
#include <cstdlib>
#include <ctime> 
#include <fstream>
#include <string>

Board CSPRecursion(Board, bool& found);
Board constraintSatisfactionStart(Board currentBoard, int newBoard[81]);
void humanPlaying(Board, Board);

void destroy(Variable*);
int main(int argc, char* argv[])
{
	cout <<"welcome, please chose a puzzle diffuclty from 0 to 3: " << endl;
	int input = 0;
	int count = 0;
	int i = 0;
	int tempBoard[81];

	cin >> input;
	ifstream fin;
	fin.open("puzzles.txt");
	char fChar = 'a';
	while(!fin.eof())
	{
		fin.get(fChar);
		if(fChar == '\n')
		{
			count++;
			continue;
		}
		else if(count == input)
		{
			tempBoard[i] = fChar - '0';
			i++;
		}
		else if(count > input)
			break;
	}
		//fin.seekg(ios_base::beg);


	cout << "continuing with this board: " << endl;
	Board board(tempBoard);
	board.displayBoard();
	cout << endl << endl;
	Board finalBoard;
	Variable* MCLRoot;
	Variable* LCLRoot;
	finalBoard = constraintSatisfactionStart(board,tempBoard);

	humanPlaying(board, finalBoard);

	
}

void humanPlaying(Board humanBoard,Board finalBoard)
{
	cout << "Begin." << endl;
	int x, y, digit = -1;
	char input, input1, input2;
	while(!humanBoard.isFinished())
	{
		humanBoard.displayBoard();
		cout << "please enter your choice in the form <x> <enter> <y> <enter> <digit> <enter>" << endl;
		cin >> input;
		cin >> input1;
		cin >> input2;
		x = input - '0';
		y = input1 - '0';
		digit = input2 - '0';
		//cout << "before segfault" << endl;
		if(finalBoard.getValueOfCell(x, y) != digit)
		{
		//	cout << "after segfault" << endl;
			cout <<"That move eventually violates a constraint." << endl;
			cout <<"I reccomend using " << finalBoard.getValueOfCell(x, y) << " there. " << endl;
		}
		else if(finalBoard.getValueOfCell(x, y) == digit && humanBoard.getValueOfCell(x, y) == 0)
			humanBoard.humanBoardUpdate(x,y,digit);
		else if(humanBoard.getValueOfCell(x, y) != 0)
			cout << "That spot is already taken" << endl;

	}

}
Board constraintSatisfactionStart(Board currentBoard,int newBoard[81])
{
	bool found = false;
	while(!currentBoard.isFinished())
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
					if(finalBoard.isFinished())
					{
						// cout << "returns" << endl;
						// destroy(LCLRoot);
						// destroy(MCLRoot);
						return finalBoard;
					}
				}
				else
					LCLRoot = LCLRoot->getNext();
			}
			
			MCLRoot = MCLRoot->getNext();
		}
	}
	cout << "A solution wasn't found" << endl;
}
Board CSPRecursion(Board currentBoard, bool& found)
{
	Board finalBoard;
	//cout << "does it get to here" << endl;
	int newBoard[81];
	if(found == true || currentBoard.isFinished())
	{
		//cout <<"did it make it this far" << endl; 
		//found = true;
		return currentBoard;
	}

	else
	{
		Variable* MCLRoot;
		Variable* LCLRoot;
		MCLRoot = currentBoard.getMostConstrainedList();
		Variable* test;
		test = MCLRoot;
		int x, y, value;
		/*while(test != NULL)
			{
				test->getXY(x, y);
				cout << "X: " << x << " Y: " << y << endl;
				test = test->getNext();
			}*/
		
		while(MCLRoot != NULL)
		{
			//cout << "testing" << endl;
			LCLRoot = currentBoard.getLeastConstrainingList(MCLRoot);
			while(LCLRoot != NULL)
			{
				//cout << "2 ";

				if(currentBoard.forwardChecking(LCLRoot))
				{
					LCLRoot->getXY(x, y);
					LCLRoot->getValue(value);

					//c//out << "testing3" << endl;
					//cout << LCLRoot-> getConstrained() << endl;
					currentBoard.getNewBoard(LCLRoot, newBoard);
					//cout << "testing5" << endl;
					/*cout << "<what is in newBoard> " << endl;
					for(int i = 0; i < 81; i++)
					{
						cout << newBoard[i] << " ";
						if(i %9 == 0)
							cout << endl;
					}
					cout << "<what is in newBoard/>" << endl;*/

					Board updatedBoard(newBoard);
					//cout << "testing6" << endl;
					//cout << "bool" << found << endl;
					/*cout << endl;
					updatedBoard.displayBoard();
					cout << endl;*/
					finalBoard = CSPRecursion(updatedBoard, found);
					//cout << "testing7" << endl;
					if(finalBoard.isFinished())
					{
						Variable* tnt = new Variable;
						// if(LCLRoot == NULL)
						// 	cout << "is NULL" << endl;
						// if(LCLRoot != NULL)
						// 	destroy(LCLRoot);
						// if(MCLRoot != NULL)
						// 	destroy(MCLRoot);
						return finalBoard;
					}
				}
				//cout <<"backstracking within a node" << endl;
				LCLRoot = LCLRoot->getNext();
			}
			//cout << "backtracking for MCLRoot" << endl;
			MCLRoot = MCLRoot->getNext();
		}
	}
}

void destroy(Variable* element)
{
	Variable* forwardT;
	Variable* forwardD;
	Variable* backwardT;
	Variable* backwardD;
	if(element->getNext() != NULL)
	{
		forwardT = element->getNext();
		while(forwardT -> getNext() != NULL)
		{
			forwardD = forwardT;
			forwardT = forwardT->getNext();
			delete forwardD;
		}
		delete forwardT;
	}
	if(element->getPrev() != NULL)
	{
		backwardT = element->getPrev();
		while(backwardT -> getPrev() != NULL)
		{
			backwardD = backwardT;
			backwardT = backwardT->getPrev();
			delete backwardD; 
		}
		delete backwardT;
	}
	delete element;
	
}
