
class Cell
{

public:
Cell();
Cell(int newXLoc, int newYLoc, int newDigit, int newSquareNum);
void setLocation(int newXloc, int newYLoc);
void getLocation(int currentX, int currentY, int currentSquareNum);
void setDigit(int newDigit);
void getDigit(int currentDigit);
void setDomain(int newDomain[9]);
void getDomain(int currentDomain[9]);

protected:
int xloc;
int yloc;
int digit;
int squareNum;
int Domain[9];

};