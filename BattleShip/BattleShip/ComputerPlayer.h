#ifndef ComputerPlayer_H
#define ComputerPlayer_H

#include <iostream>
#include "Player.h"
#include "Field.h"
#include "Orientation.h"

using namespace std;
class ComputerPlayer : public Player
{
private:
	Field* enemyField_;
	Cell previousShoot;
    Cell lastSuccessfulShoot;
	bool isInjuredShipPresent;
	Orientatoin shootOrientation;
	void SetBorders (); 
	Point ShootWithOrientation ();
	Point RandomShootAroundCell ();
	void FindOrientation ();


public:
	ComputerPlayer ();
	ComputerPlayer (Field * enemyField);
	~ComputerPlayer ();
	Point Shoot () override;
	Point IntelectualShoot ();
};

#endif