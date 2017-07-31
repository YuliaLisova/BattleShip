#ifndef Cell_H
#define Cell_H

#include "CellPosition.h"
#include "CellState.h"
#include "Observable.h"

class Cell : public Observable
{
public:
	int rowNumber_;
	int columnNumber_;
	CellPosition cellPosition_;
	CellState cellstate_;
	Cell ();
	~Cell ();

};

#endif