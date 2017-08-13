#ifndef Field_H
#define Field_H

#include "Cell.h"
#include "Observable.h"

class Field: public Observable
{
public:
	static const int size_ = 10;
	Cell array [size_][size_] ;

	Field ();
	
	~Field ();

	void ClearField ();
	
};


#endif
