#include "sudokuCell.h"
class Board

{

public:
Board();
Board(int board[81]);
updateBoard(int xOfChanged, int yOfChanged);
protected:
Cell cells[81];

};