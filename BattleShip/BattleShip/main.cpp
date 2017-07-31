#include <iostream>

#include<ctime>

#include<windows.h>

#include "Controller.h"
#include "Field.h"
#include "Navy.h"
#include "View.h"



void main ()
{
	 system("mode con cols=80 lines=50");

	srand((unsigned)time(NULL));
	Controller controller;


	Navy* userNavy = new Navy ();
	Field* userField = new Field ();

	Navy* computerNavy = new Navy ();
	Field* computerField = new Field ();

	

	int deckCount = 4;
	int shipCount = 1;

	for (deckCount; deckCount > 0; deckCount--, shipCount++) 
	{
		for (int count = 0; count < shipCount; count++) 
		{
			Ship * userShip = new Ship(deckCount);
			Ship * computerShip = new Ship(deckCount);
			userNavy->ships_.push_back(userShip);
			computerNavy ->ships_.push_back(computerShip);
			
		}
	}
			

	

	controller.SetShipsOnTheField(userField, userNavy);


	controller.SetShipsOnTheField(computerField, computerNavy);


	UserPlayer userPlayer;
	
	ComputerPlayer  computerPlayer (userField);
	View* view =  new View (userField, computerField);
	view->Draw();

	Point point;
	bool isHit = false;
	
	
	
	while (computerNavy->isAlive_  == true && userNavy->isAlive_ == true)
	{
		do{
		      cout<<"Users shoot"<<endl;
		      point = userPlayer.Shoot();
		      isHit = controller.CheckShootRight(point, computerField);
		      computerField->Notify();
			  
	       }
		while (isHit !=false && computerNavy->isAlive_== true );

		if (computerNavy->isAlive_== false)
		{
			cout<<"You are winner"<<endl;
			cout<<endl<<"break"<<endl;
			break;
		}

		do
		    {
				cout<<endl<<"Computer's  shoot"<<endl;
				Sleep(1000);
		        point = computerPlayer.Shoot();
		       isHit = controller.CheckShootRight(point, userField);
		
		       userField->Notify();
		   }

			while (isHit !=false && userNavy->isAlive_ == true) ;

			if (userNavy->isAlive_== false)
		{
			cout<<"Computer is winner"<<endl;
			cout<<endl<<"break"<<endl;
			break;
		}

	}

	cout<<endl<<"game over"<<endl;


	
	delete userField;
	delete computerField;
	
	delete view;
	cout<<endl<<"deleted"<<endl;
	for (int i = 0; i< userNavy->ships_.size(); i ++)
	{
		if (userNavy->ships_[i] != nullptr)
		{
			delete userNavy->ships_[i];
			userNavy->ships_[i]= nullptr;
			cout<<i<<"deleted"<<endl;
		}
	}

	for (int i = 0; i< computerNavy->ships_.size(); i ++)
	{
		if (computerNavy->ships_[i] != nullptr)
		{
			delete computerNavy->ships_[i];
			computerNavy->ships_[i] = nullptr;
			cout<<i<<"deleted"<<endl;
		}
	}

	delete userNavy;
	delete computerNavy;
}