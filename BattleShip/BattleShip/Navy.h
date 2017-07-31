#ifndef Navy_H
#define Navy_H
#include <vector>
#include "Ship.h"
#include "Observer.h"
using namespace std;

class Navy : public Observer
{
public:
	vector <Ship*> ships_;
	bool isAlive_;
	int countShips_;	
	Navy ();	
	~Navy ();
	int getCountShips () const;

	void Update () override;

private:
	bool CheckNavyAlive ();
	
};


#endif