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


bool  ship_is_good
    (
        int         size, 
        bool        is_horiz, 
        int         row_top, 
        int         col_left, 
        const Field  field
    )
{
	const int  FIELD_DIM   = 10;

    if(is_horiz)
    {
        for(int i =   std::max(0,              row_top - 1); 
                i <=  std::min( - 1,  row_top + 1); 
                ++i)
        {
            for(int j =   std::max(0,              col_left - 1); 
                    j <=  std::min(FIELD_DIM - 1,  col_left + size); 
                    ++j)
            {
				if(field.array[i][j].cellPosition_ != EMPTY ) return false;
            }        
        }
        return  true;
    }
    else//вертикальный
    {
        for(int i =   std::max(0,             row_top - 1); 
                i <=  std::min(FIELD_DIM - 1, row_top + size); 
                ++i)
        {
            for(int j =   std::max(0,             col_left - 1); 
                    j <=  std::min(FIELD_DIM - 1, col_left + 1); 
                    ++j)
            {
                if(field.array[i][j].cellPosition_ != EMPTY ) return false;
            }        
        }
        return  true;
    }
}


void  set_ship_with_size(Ship* ship, Field * field)
{
	const int  FIELD_DIM   = 10;
	int size = ship->size_;

    bool  is_horiz  = rand() % 2 == 0;
    int   row_top   = 0;
    int   col_left  = 0;
 
    do
    {
        do
        {
            row_top = rand() % FIELD_DIM;
        }while(   !is_horiz 
               && row_top > FIELD_DIM - size);
 
        do
        {
            col_left = rand() % FIELD_DIM;
        }while(   is_horiz 
               && col_left > FIELD_DIM - size);        
    }while(!ship_is_good(size, is_horiz, row_top, col_left,  * field)); 
 
    if(is_horiz)
    {
        for(int j = col_left; j < col_left + size; ++j)
        {
			field->array[row_top][j].cellPosition_ = DECK;

			ship->decks_.push_back(&field->array[row_top][j]);
				field->array[row_top][j].AddObserver(ship);
        }
    }
    else//вертикальный
    {
        for(int i = row_top; i < row_top + size; ++i)
        {
			field->array[i][col_left].cellPosition_= DECK;
			ship->decks_.push_back(&field->array[i][col_left]);
				field->array[i][col_left].AddObserver(ship);
        }    
    }
}

	bool Controller:: IsItPossible (const Field& field, const int & deckNumbers,const int & orientation, const  int & y, const int & x) const
{
	if (field.array[y][x].cellPosition_ != EMPTY) return false;
	switch (orientation)
	{
	  case 1:
		  if (x + deckNumbers > 9) return false;
		  else 
		  {
		  
			   bool returning = true;
			  for (int i = x+1; i <= deckNumbers; i ++)
		      {
			  if (field.array[i][x].cellPosition_ != EMPTY) returning =  false;
			 // break;
		      }
             return returning;
		  }
	
		
		  break;
	  case 2:
		  if (y + deckNumbers > 9) return false;


		
		  else 
		  
		  {
			  bool returning = true;
			  for (int i = y+1; i <= deckNumbers; i ++)
		      {
			  if (field.array[i][x].cellPosition_ != EMPTY) returning =  false;
			 // break;
		      }
             return returning;
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

