
using namespace std;
class Cell
{

public:
Cell();
Cell(int newXLoc, int newYLoc, int newDigit, int newSquareNum);
~Cell();
void setLocation(int newXloc, int newYLoc);
void getLocation(int &currentX, int &currentY, int &currentSquareNum);
void setDigit(int newDigit);
void getDigit(int &currentDigit);
void setDomain(int newDomain[9]);
void getDomain(int currentDomain[9]);
void setNumbValInDomain(int newNumbValInDomain);
void getNumbValInDomain(int &currentNumbvalInDomain);

protected:
int xLoc;
int yLoc;
int digit;
int squareNum;
int domain[9];
int numbValInDomain;

};