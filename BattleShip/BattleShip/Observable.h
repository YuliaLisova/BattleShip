#ifndef Observable_H
#define Observable_H

#include <vector>
#include "Observer.h"
using namespace std;
class Observable
{
private:
	vector <Observer*> observers_;
	
public:
	Observable();
	virtual ~Observable();
	void AddObserver(Observer* observer);	
	void Notify();
	
};

#endif 