#include "Navy.h"
#include <iostream>

using namespace std;

	Navy :: Navy ()
	{
		isAlive_ = true;
	}

	Navy ::~Navy()
	{

	}

	int Navy :: getCountShips () const
	{
		return ships_.size();
	}

	bool Navy :: CheckNavyAlive () 
	{
		int countInjuredShips = 0;
		{
			for (int i = 0; i< this->ships_.size(); i++)
			{
				if (this->ships_[i]->isAlive_ == false)
					countInjuredShips ++;
			}
		}

		if (countInjuredShips == this->ships_.size())
		{
			this->isAlive_ = false;
			cout<<"navy fall"<<endl;
			cout<<endl<<isAlive_;
		}

		return this->isAlive_;
	}

	void Navy :: Update ()
	{

		cout<<endl<<" i am notified"<<endl;
		CheckNavyAlive ();
	}