#ifndef BOARD_H
#define BOARD_H
#include "sudokuVariable.h"
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
protected:
	Cell cells[9][9];
	bool finished;
};
#endif