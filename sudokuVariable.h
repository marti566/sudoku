#ifndef	VARIABLE_H
#define VARIABLE_H

class Variable
{

public:
Variable();
~Variable();
void setNext(Variable*);
Variable* getNext();
void setPrev(Variable*);
Variable* getPrev();
void setXY(int newX, int newY);
void getXY(int &currentX, int &currentY);
void setValue(int newValue);
void getValue(int &currentValue);
void setConstrained(int newConstrained);
int getConstrained();
protected:

int x;
int y;
int value;
int constrainedAmount;
Variable* previous;
Variable* next;
};

#endif