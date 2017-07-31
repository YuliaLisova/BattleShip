#include "UserPlayer.h"

using namespace std;

UserPlayer ::UserPlayer()
{

}

UserPlayer :: ~UserPlayer ()
{

}

 bool UserPlayer :: IsCoordinatesRight (const char & charX, const int & intY)
{
	int intX = static_cast <int> (charX);
	if (intY >=1 && intY <=10)
	{
		if (intX >= 65 && intX <= 74) 
		   {
			
			 return true;
		   }
		else if (intX >= 97 && intX <= 106) 
			
		  {
			
			 return true;
		  }
		else return false;
	}
	else return false;
}

int UserPlayer :: TransferLettersToHorisontalCoordinate (const char & charX)
{
	int intX = static_cast <int> (charX);
	
	if  ( intX >= 65 && intX <= 74)
	{
		for (int i = 65, iteration = 0; i<=74; i++, iteration ++)
		{
			if (intX == i)
				return iteration;
		}
	}

	else if  (intX >= 97 && intX <= 106)
	{
		for (int i = 97, iteration = 0; i<=106; i++, iteration ++)
		{
			if (intX == i)
				return iteration;
		}
	}

	else return 0;
}

Point UserPlayer ::Shoot ()
{
	char charX;
	int intX;
	int intY;
	do{
		cout<< "Enter coordinates to attack: ";
		cout<<"horizsontal (A-J): ";
		cin>>charX;
		cout<<"vertical (1-10) ";
		cin>>intY;

		if ( !IsCoordinatesRight (charX, intY))
			cout<<"wrong coordinates"<<endl;
	  }
	while ( !IsCoordinatesRight (charX, intY));
	intX =TransferLettersToHorisontalCoordinate (charX);
	return Point (intY-1, intX);
}