#ifndef ComputerPlayer_H
#define ComputerPlayer_H

#include <iostream>
#include "Player.h"
#include "Field.h"

using namespace std;
class ComputerPlayer : public Player
{
private:
	Field* enemyField_;
public:
	ComputerPlayer ();
	ComputerPlayer (Field * enemyField);
	~ComputerPlayer ();
	Point Shoot () override;

};

#endif