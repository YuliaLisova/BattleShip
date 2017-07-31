#ifndef Field_H
#define Field_H

#include "Cell.h"
#include "Observable.h"

class Field: public Observable
{
public:
	Cell array [10][10] ;

	Field ();
	
	~Field ();

	void ClearField ();
	
};


#endif
