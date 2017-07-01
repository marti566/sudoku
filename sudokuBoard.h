#ifndef BOARD_H
#define BOARD_H
#include "sudokuVariable.h"
#include "sudokuCell.h"
using namespace std;
class Board

{

public:
	Board();
	Board(int board[81]);
	
	bool isFinished();
	Variable* getMostConstrainedList();
	Variable* getLeastConstrainingList(Variable* variable);
	bool forwardChecking(Variable* Move);
	void getNewBoard(Variable* Move, int newBoard[81]);
	void displayBoard();
	int getValueOfCell(int x, int y);
	void humanBoardUpdate(int x, int y, int digit);
	int countZeros();
protected:
	Cell cells[9][9];
	bool finished;
};
#endif