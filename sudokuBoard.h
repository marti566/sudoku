#ifndef CELL_H
#define CELL_H

#include "sudokuCell.h"
using namespace std;
class Board

{

public:
Board();
Board(int board[81]);
void updateBoard(int xOfChanged, int yOfChanged);
void getLeastConstrained(int x, int y);
protected:
Cell cells[81];

};

#endif