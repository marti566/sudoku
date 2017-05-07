#ifndef BOARD_H
#define BOARD_H
//#include "sudokuCell.h"
using namespace std;
class Board

{

public:
	Board();
	Board(int board[81]);
	void updateBoard(int xOfChanged, int yOfChanged);
	void getLeastConstrained(int x, int y);
	void displayBoard();
protected:
	Cell cells[9][9];

};
#endif