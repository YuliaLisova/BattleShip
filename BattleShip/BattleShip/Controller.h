#ifndef Game_H
#define Game_H

#include "UserPlayer.h"
#include "ComputerPlayer.h"
#include "Navy.h"
#include "Field.h"

class Controller 
{
public:
	
	Controller ();
	~Controller ();

	bool CheckShootRight (const Point& point, Field* field);
	void SetShipsOnTheField (Field * field,  Navy* navy);

private:

	void SetShipRandomly(Field * field, Ship* ship);
	bool IsItPossible (const Field& field, const int & deckNumbers,const int & orientation, const  int & y, const int & x) const;

};


#endif