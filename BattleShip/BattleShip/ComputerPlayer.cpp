#include "ComputerPlayer.h"

ComputerPlayer ::ComputerPlayer()
{

}


ComputerPlayer :: ComputerPlayer (Field * enemyField)
{
	enemyField_ = enemyField;
}

ComputerPlayer :: ~ComputerPlayer ()
{

}

Point ComputerPlayer :: Shoot ()
{
	int xCoordinate ;
	int yCoordinate ;
	
	do 
	{
	 xCoordinate = rand()%10 ;
	 yCoordinate = rand()%10 ;
	
	}
	while (this->enemyField_->array[xCoordinate][yCoordinate].cellstate_ !=CLEAN);
	return Point (xCoordinate, yCoordinate);
}