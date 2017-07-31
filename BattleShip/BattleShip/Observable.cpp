#include "Observable.h"

Observable :: Observable()
{
}

Observable :: ~Observable()
{

}

void Observable ::AddObserver (Observer* observer)
{
	this->observers_.push_back(observer);
	
}

void Observable ::Notify ()
{
	
	for (int i = 0; i< observers_.size(); i ++)
	{
		observers_[i]->Update();
	}
}