
#include <iostream>
#include "Ship.h"

using namespace std;

Ship :: Ship()
{

}

Ship :: Ship (const int & size )
{
	size_ = size;
}

Ship :: ~Ship ()
{
	cout<<endl<<"ship deleted"<<endl;
}

void  Ship :: CheckShipAlive ()
{
	int countInjuredDcks = 0;
	for (int i =0; i < this->decks_.size(); i++)
	{
		if (this->decks_[i]->cellstate_ == INJURED)
			countInjuredDcks ++;
	}

	if (countInjuredDcks == decks_.size())
	{
		this->isAlive_ = false;

		for (int i =0; i < this->decks_.size(); i++)
	  {
		if (this->decks_[i]->cellstate_ = KILLED);
			
	  }

		Notify();
   }
}

void Ship :: Update ()
{
	CheckShipAlive ();
}