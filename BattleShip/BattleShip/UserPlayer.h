#ifndef UserPlayer_H
#define UserPlayer_H

#include <iostream>
#include "Player.h"

using namespace std;
class UserPlayer : public Player
{
public:
	UserPlayer ();
	~UserPlayer ();
	Point Shoot () override;
private:
	bool IsCoordinatesRight (const char & charX, const int & intY);
	int TransferLettersToHorisontalCoordinate (const char & charX);
};

#endif