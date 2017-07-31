#ifndef Ship_H
#define Ship_H

#include <vector>
#include "Cell.h"
#include "Observer.h"

using namespace std;

class Ship : public Observer, public Observable
{


public:
	vector <Cell*> decks_;
	bool isAlive_;
	int size_;

	Ship ();


	Ship (const int & size);
	

	~Ship ();

	void CheckShipAlive ();
	void Update () override;
	
};


#endif