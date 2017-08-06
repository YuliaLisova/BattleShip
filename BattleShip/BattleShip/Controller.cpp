#include <algorithm>
#include <ctime>
#include <iostream>
#include <cstdlib>

#include "Controller.h"

using namespace std;

   Controller :: Controller ()
   {

   }
   Controller ::	~Controller ()
   {

   }

	bool Controller :: CheckShootRight (const Point& point, Field * field)
	{
		if (field->array[point.xPosition_][point.yPosition_].cellPosition_ == DECK)
		{
			field->array[point.xPosition_][point.yPosition_].cellstate_ = INJURED;

			field->array[point.xPosition_][point.yPosition_].Notify();

			return true;
		}

		else 
		{
			field->array[point.xPosition_][point.yPosition_].cellstate_ = MISSED;
			return false;
		}

	}



	void Controller :: SetShipRandomly (Field * field, Ship* ship)
	{
	int k=1,  deckNumbers = ship->size_;
        int row,col;//строка - столбец массива
        int gorver;
		int a =0;
		
		ship->decks_.clear();

		do{
		gorver=1+rand()%2;//по горизонтали или по вертикали
		row=rand()%10;
		col=rand()%10;
		}

		
		while (!IsItPossible(*(field), deckNumbers, gorver, row, col));

		
        switch(gorver)
        {
        case 2:     //вертикаль  
			
			if (row >0 )
			{
				field->array[row-1][col].cellPosition_ = BORDER;
				if (col >0 )
					field->array[row-1][col-1].cellPosition_ = BORDER;
				if (col <9 )
					field->array[row-1][col+1].cellPosition_ = BORDER;
			}

            while(k<=deckNumbers)//k счетчик i текущ€€ палуба
            {                   
				if (field->array[row][col].cellPosition_ == EMPTY)
				{field->array[row][col].cellPosition_ = DECK;
				ship->decks_.push_back(&field->array[row][col]);
				field->array[row][col].AddObserver(ship);
				}
				if (col > 0)
					field->array[row][col-1].cellPosition_ = BORDER;
				if (col < 9 )

					field->array[row][col+1].cellPosition_ = BORDER;
				
                row++;
                deckNumbers--;
            } 

			
			if (row <= 9 )
			{
				field->array[row][col].cellPosition_ = BORDER;
				if (col >0 )
					field->array[row][col-1].cellPosition_ = BORDER;
				if (col <=9 )
					field->array[row][col+1].cellPosition_ = BORDER;
			}


            break;
        case 1:         //горизонталь 

			if (col > 0)
			{
				field->array[row][col-1].cellPosition_ = BORDER;
				if (row > 0)
					field->array[row-1][col-1].cellPosition_ = BORDER;
				if (row < 9)
					field->array[row+1][col-1].cellPosition_ = BORDER;
			}

            while(k<=deckNumbers)
            {
				if (field->array[row][col].cellPosition_ == EMPTY)
               { field->array[row][col].cellPosition_ = DECK;
				ship->decks_.push_back(&field->array[row][col]);
				field->array[row][col].AddObserver(ship);
				}
				if (row >0 )
					field->array[row-1][col].cellPosition_ = BORDER;
				if (row <=9 )
					field->array[row+1][col].cellPosition_ = BORDER;

                col++;
                deckNumbers--;
            }   

			if (col <=9)
			{
				field->array[row][col].cellPosition_ = BORDER;
				if (row > 0) 
					field->array[row-1][col].cellPosition_ = BORDER;
				if (row < 9)
					field->array[row+1][col].cellPosition_ = BORDER;
			}
            break;
        }
		//navy->ships.push_back(*ship);
}






	bool Controller:: IsItPossible (const Field& field, const int & deckNumbers, const int & orientation, const  int & x, const int & y) const
{
	switch (orientation)
		{
		case 1://horizontal
			{if (y + deckNumbers > 10) return false;
			else 
			{
				for (int i = y, iteration = 0; iteration < deckNumbers; i ++, iteration ++)
				{if (field.array[x][i].cellPosition_ != EMPTY) return false;}			
			}
			}
			break;

		case 2:
			{
			if (x + deckNumbers > 10) return false;
			else 
			{
				for (int i = x, iteration = 0; iteration < deckNumbers; i ++, iteration ++)
				{
					if (field.array[i][y].cellPosition_ != EMPTY) return false;

				}			
			}
			}
			break;
		}

	

	return true;
}


void Controller :: SetShipsOnTheField (Field * field,  Navy* navy)
{

	field->ClearField();


	for (int i = 0; i<navy->ships_.size(); i++)
	{
		SetShipRandomly(field, navy->ships_[i]);
		navy->ships_[i]->AddObserver(navy);
		//cout<<"ship "<<navy->ships_[i]->size_<<"set "<<endl;
		/*set_ship_with_size(navy->ships_[i], field);
		navy->ships_[i]->AddObserver(navy);*/

	}

	
}

