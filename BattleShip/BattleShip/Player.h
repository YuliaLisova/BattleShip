#ifndef PLAYER_H
#define PLAYER_H

#include "Field.h"
#include "Navy.h"
#include "Point.h"

class Player
{
public:
	
	Player ();
	virtual ~Player ();
	virtual Point Shoot() = 0;

};

#endif