#include "ComputerPlayer.h"

ComputerPlayer ::ComputerPlayer()
{

}


ComputerPlayer :: ComputerPlayer (Field * enemyField)
{
	enemyField_ = enemyField;
	previousShoot.rowNumber_=-1;
	previousShoot.columnNumber_=-1;
	previousShoot.cellstate_=MISSED;
	shootOrientation = DEFAULT;
	isInjuredShipPresent = false;
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


Point ComputerPlayer :: ShootWithOrientation ()
{
	Point NextShoot  = Shoot();
	if (shootOrientation ==  VERTICAL)
		{
			 int x = previousShoot.rowNumber_;
			 
			 if (x<9)
			 {
				 /*while (this->enemyField_->array[x+1][previousShoot.columnNumber_].cellstate_ !=CLEAN && x < 9)
				 {x++;}*/
				 while (x < 9)
				 {
					 if (this->enemyField_->array[x+1][previousShoot.columnNumber_].cellstate_ == CLEAN)
					 {
						 x++;
						 break;
					 }

					 if (this->enemyField_->array[x+1][previousShoot.columnNumber_].cellstate_ == INJURED)
					 {
						 x++;
					 }

					 if (this->enemyField_->array[x+1][previousShoot.columnNumber_].cellstate_ == MISSED)
					 {
						 x = previousShoot.rowNumber_;
						 break;
					 }


				 }


			 }
				 if (x == previousShoot.rowNumber_)
				 {
					while (x > 0)
				    {
					     if (this->enemyField_->array[x-1][previousShoot.columnNumber_].cellstate_ == CLEAN)
					     {
						     x--;
						     break;
					     }

					     if (this->enemyField_->array[x-1][previousShoot.columnNumber_].cellstate_ == INJURED)
					     {
						     x--;
					     }

					     if (this->enemyField_->array[x-1][previousShoot.columnNumber_].cellstate_ == MISSED)
					     {
						     x = previousShoot.rowNumber_;
						     break;
					     }
				     }
				 }
			 NextShoot.xPosition_= x;
			 NextShoot.yPosition_=previousShoot.columnNumber_;
		}

		else if (shootOrientation == HORIZONTAL)
		{
			int y = previousShoot.columnNumber_;

			if (y < 9)
			{
			   /* while (this->enemyField_->array[previousShoot.rowNumber_][y+1].cellstate_ !=CLEAN && y < 9)
			    {y++;}*/
				while (y < 9)
				{
					if (this->enemyField_->array[previousShoot.rowNumber_][y+1].cellstate_ == CLEAN)
					{
						y++;
						break;
					}

					if (this->enemyField_->array[previousShoot.rowNumber_][y+1].cellstate_ == INJURED)
					{
						y++;
					}

					if (this->enemyField_->array[previousShoot.rowNumber_][y+1].cellstate_ == MISSED)
					{
						y = previousShoot.columnNumber_;
						break;
					}


				}

			}
			if (y == previousShoot.columnNumber_)
			{
				/*while (this->enemyField_->array[previousShoot.rowNumber_][y-1].cellstate_ !=CLEAN && y > 0) 
			    {y--;}*/
				while (y > 0)
				{
					if (this->enemyField_->array[previousShoot.rowNumber_][y-1].cellstate_ == CLEAN)
					{
						y--;
						break;
					}

					if (this->enemyField_->array[previousShoot.rowNumber_][y-1].cellstate_ == INJURED)
					{
						y--;
					}

					if (this->enemyField_->array[previousShoot.rowNumber_][y-1].cellstate_ == MISSED)
					{
						y = previousShoot.columnNumber_;
						break;
					}


				}
			}

			NextShoot.xPosition_= previousShoot.rowNumber_;
			NextShoot.yPosition_ = y;
		}
	return NextShoot;
}

Point ComputerPlayer :: IntelectualShoot ()
{
	Point NextShoot  = Shoot();
	
	if (previousShoot.rowNumber_ != -1)
	{
		previousShoot.cellstate_= this->enemyField_->array[previousShoot.rowNumber_][previousShoot.columnNumber_].cellstate_;
	}

	if (previousShoot.cellstate_ == INJURED)
	{
		isInjuredShipPresent = true;
		lastSuccessfulShoot = previousShoot;
	}

	if (previousShoot.cellstate_ == MISSED && shootOrientation == DEFAULT && isInjuredShipPresent)
	{
		NextShoot = RandomShootAroundCell ();
	}
		
	if (previousShoot.cellstate_ == KILLED )
	{
		isInjuredShipPresent = false;
		SetBorders ();
		previousShoot.cellstate_=MISSED;
	    shootOrientation = DEFAULT;
		//NextShoot = Shoot();
	}
	else if (previousShoot.cellstate_ == INJURED && shootOrientation != DEFAULT)
	{
		NextShoot = ShootWithOrientation ();
	}

	else if (previousShoot.cellstate_ == INJURED && shootOrientation == DEFAULT)
	{
		int f =0;
		FindOrientation ();

		if (shootOrientation != DEFAULT)
		{
			NextShoot = ShootWithOrientation ();
		}

		else 
		{
			NextShoot = RandomShootAroundCell ();
           //to do -random shoot around current cell;
			
		}

	}

	else if (previousShoot.cellstate_ == MISSED && shootOrientation != DEFAULT)
	{
		if (shootOrientation == HORIZONTAL)
		{
			if (previousShoot.columnNumber_ < 9 && this->enemyField_->array[previousShoot.rowNumber_][previousShoot.columnNumber_+1].cellstate_ == INJURED)
			{
				previousShoot.columnNumber_ +=1;
			}
			else if (previousShoot.columnNumber_ >0 && this->enemyField_->array[previousShoot.rowNumber_][previousShoot.columnNumber_-1].cellstate_ == INJURED)
			{
				previousShoot.columnNumber_ -= 1;
			}
		}
		else if (shootOrientation == VERTICAL)
		{
			if (previousShoot.rowNumber_ < 9 && this->enemyField_->array[previousShoot.rowNumber_+1][previousShoot.columnNumber_].cellstate_ == INJURED)
			{
				previousShoot.rowNumber_ +=1;
			}
			else if (previousShoot.rowNumber_  > 0 && this->enemyField_->array[previousShoot.rowNumber_ -1 ][previousShoot.columnNumber_].cellstate_ == INJURED)
			{
				previousShoot.rowNumber_ -= 1;
			}
		}

		NextShoot = ShootWithOrientation ();
	}

	previousShoot.rowNumber_ = NextShoot.xPosition_;
	previousShoot.columnNumber_=NextShoot.yPosition_;
	return NextShoot;
}


void ComputerPlayer :: FindOrientation ()
{
	if (previousShoot.rowNumber_ > 0 && this->enemyField_->array[previousShoot.rowNumber_-1][previousShoot.columnNumber_].cellstate_ == INJURED ||
		previousShoot.rowNumber_ > 0 && this->enemyField_->array[previousShoot.rowNumber_-1][previousShoot.columnNumber_].cellstate_ == KILLED)
			shootOrientation = VERTICAL;
		else if (previousShoot.rowNumber_ < 9 && this->enemyField_->array[previousShoot.rowNumber_+1][previousShoot.columnNumber_].cellstate_ == INJURED ||
			previousShoot.rowNumber_ < 9 && this->enemyField_->array[previousShoot.rowNumber_+1][previousShoot.columnNumber_].cellstate_ == KILLED)
			shootOrientation = VERTICAL;
		else if (previousShoot.columnNumber_ > 0 && this->enemyField_->array[previousShoot.rowNumber_][previousShoot.columnNumber_-1].cellstate_ == INJURED ||
			previousShoot.columnNumber_ > 0 && this->enemyField_->array[previousShoot.rowNumber_][previousShoot.columnNumber_-1].cellstate_ == KILLED)
			shootOrientation = HORIZONTAL;
		else if (previousShoot.columnNumber_ < 9 && this->enemyField_->array[previousShoot.rowNumber_][previousShoot.columnNumber_+1].cellstate_ == INJURED ||
			previousShoot.columnNumber_ < 9 && this->enemyField_->array[previousShoot.rowNumber_][previousShoot.columnNumber_+1].cellstate_ == KILLED)
			shootOrientation = HORIZONTAL;
		else {}
}
Point ComputerPlayer :: ShootAroundCell ()
{
	Point NextShoot;
	NextShoot.xPosition_= lastSuccessfulShoot.rowNumber_;
	NextShoot.yPosition_= lastSuccessfulShoot.columnNumber_;

	if (lastSuccessfulShoot.columnNumber_ < 9 &&
		this->enemyField_->array[lastSuccessfulShoot.rowNumber_][lastSuccessfulShoot.columnNumber_ +1].cellstate_ == CLEAN)
	{
		NextShoot.yPosition_ += 1;
	}

	else if (lastSuccessfulShoot.columnNumber_ > 0 &&
		this->enemyField_->array[lastSuccessfulShoot.rowNumber_][lastSuccessfulShoot.columnNumber_ -1].cellstate_ == CLEAN)
	{
		NextShoot.yPosition_ -= 1;
	}

	else if (lastSuccessfulShoot.rowNumber_ < 9 &&
		this->enemyField_->array[lastSuccessfulShoot.rowNumber_ + 1][lastSuccessfulShoot.columnNumber_].cellstate_ == CLEAN)
	{
		NextShoot.xPosition_ += 1;
	}

	else if (lastSuccessfulShoot.rowNumber_ > 0 &&
		this->enemyField_->array[lastSuccessfulShoot.rowNumber_ - 1][lastSuccessfulShoot.columnNumber_].cellstate_ == CLEAN)
	{
		NextShoot.xPosition_ -= 1;
	}

	return NextShoot;
}

Point ComputerPlayer :: RandomShootAroundCell ()
{
	shotAroundCell nextCell;
	do 
	{
		nextCell = shotAroundCell(rand()%4);
	}
		while (!IsCellClean(nextCell));

	Point NextShoot;
	NextShoot.xPosition_= lastSuccessfulShoot.rowNumber_;
	NextShoot.yPosition_= lastSuccessfulShoot.columnNumber_;

	switch (nextCell)
	{
	case RIGHT:	NextShoot.yPosition_ += 1;	
		break;
	case LEFT: NextShoot.yPosition_ -= 1;
		break;
	case UP:  NextShoot.xPosition_ += 1;
		break;    
	case DOWN: NextShoot.xPosition_ -= 1;
		break;
	}

	return NextShoot;
}

bool ComputerPlayer :: IsCellClean (shotAroundCell nextCell)
{
	bool isClean = false;

	switch (nextCell)
	{
	case RIGHT:
		{
		    if (lastSuccessfulShoot.columnNumber_ < 9 &&
		        this->enemyField_->array[lastSuccessfulShoot.rowNumber_][lastSuccessfulShoot.columnNumber_ +1].cellstate_ == CLEAN)
			        isClean = true;
		}
		break;
	case LEFT:
		{
			if (lastSuccessfulShoot.columnNumber_ > 0 &&
		        this->enemyField_->array[lastSuccessfulShoot.rowNumber_][lastSuccessfulShoot.columnNumber_ -1].cellstate_ == CLEAN)
				isClean = true;
		}
		break;
	case UP:
		{
		     if (lastSuccessfulShoot.rowNumber_ < 9 &&
		        this->enemyField_->array[lastSuccessfulShoot.rowNumber_ + 1][lastSuccessfulShoot.columnNumber_].cellstate_ == CLEAN)
				isClean = true;
		}

		break;    
	case DOWN:
		{
			if (lastSuccessfulShoot.rowNumber_ > 0 &&
		        this->enemyField_->array[lastSuccessfulShoot.rowNumber_ - 1][lastSuccessfulShoot.columnNumber_].cellstate_ == CLEAN)
				isClean = true;
		}
		break;
    
	}

	return isClean;
}

void ComputerPlayer :: SetBorders ()
{
	if (shootOrientation == DEFAULT)
	{
		FindOrientation ();
	}

	if (shootOrientation == HORIZONTAL)
	{
		int y = previousShoot.columnNumber_;

		while (this->enemyField_->array[previousShoot.rowNumber_][y].cellstate_ == KILLED)
		{
			if (previousShoot.rowNumber_  >0)
			{
				this->enemyField_->array[previousShoot.rowNumber_ -1][y].cellstate_ = MISSED;
			}

			if (previousShoot.rowNumber_ < 9)
			{
				this->enemyField_->array[previousShoot.rowNumber_ +1][y].cellstate_ = MISSED;
			}

			y++;

		}

		if (y<9)
		{
			this->enemyField_->array[previousShoot.rowNumber_][y].cellstate_ = MISSED;
			if (previousShoot.rowNumber_  >0)
			{
				this->enemyField_->array[previousShoot.rowNumber_ -1][y].cellstate_ = MISSED;
			}

			if (previousShoot.rowNumber_ < 9)
			{
				this->enemyField_->array[previousShoot.rowNumber_ +1][y].cellstate_ = MISSED;
			}
		}

		y = previousShoot.columnNumber_;

		while (this->enemyField_->array[previousShoot.rowNumber_][y].cellstate_ == KILLED)
		{
			if (previousShoot.rowNumber_  >0)
			{
				this->enemyField_->array[previousShoot.rowNumber_ -1][y].cellstate_ = MISSED;
			}

			if (previousShoot.rowNumber_ < 9)
			{
				this->enemyField_->array[previousShoot.rowNumber_ +1][y].cellstate_ = MISSED;
			}

			y--;

		}

		if (y > 0 )
		{
			this->enemyField_->array[previousShoot.rowNumber_][y].cellstate_ = MISSED;
			if (previousShoot.rowNumber_  >0)
			{
				this->enemyField_->array[previousShoot.rowNumber_ -1][y].cellstate_ = MISSED;
			}

			if (previousShoot.rowNumber_ < 9)
			{
				this->enemyField_->array[previousShoot.rowNumber_ +1][y].cellstate_ = MISSED;
			}
		}
	}

	else if (shootOrientation == VERTICAL)
	{
		int x = previousShoot.rowNumber_;

		while (this->enemyField_->array[x][previousShoot.columnNumber_].cellstate_ == KILLED)
		{
			if (previousShoot.columnNumber_  >0)
			{
				this->enemyField_->array[x][previousShoot.columnNumber_ -1].cellstate_ = MISSED;
			}

			if (previousShoot.columnNumber_ < 9)
			{
				this->enemyField_->array[x][previousShoot.columnNumber_ +1].cellstate_ = MISSED;
			}

			x++;

		}

		if (x < 9)
		{
			this->enemyField_->array[x][previousShoot.columnNumber_].cellstate_ = MISSED;
			if (previousShoot.columnNumber_  >0)
			{
				this->enemyField_->array[x][previousShoot.columnNumber_ -1].cellstate_ = MISSED;
			}

			if (previousShoot.columnNumber_ < 9)
			{
				this->enemyField_->array[x][previousShoot.columnNumber_ +1].cellstate_ = MISSED;
			}
		}

		x = previousShoot.rowNumber_;

		while (this->enemyField_->array[x][previousShoot.columnNumber_].cellstate_ == KILLED)
		{
			if (previousShoot.rowNumber_  >0)
			{
				this->enemyField_->array[x][previousShoot.columnNumber_ -1].cellstate_ = MISSED;
			}

			if (previousShoot.rowNumber_ < 9)
			{
				this->enemyField_->array[x][previousShoot.columnNumber_ +1].cellstate_ = MISSED;
			}

			x--;

		}

		if (x > 0)
		{
			this->enemyField_->array[x][previousShoot.columnNumber_].cellstate_ = MISSED;
			if (previousShoot.rowNumber_  >0)
			{
				this->enemyField_->array[x][previousShoot.columnNumber_ -1].cellstate_ = MISSED;
			}

			if (previousShoot.rowNumber_ < 9)
			{
				this->enemyField_->array[x][previousShoot.columnNumber_ +1].cellstate_ = MISSED;
			}
		}
	}

	else if (shootOrientation == DEFAULT)
	{
		int x = previousShoot.rowNumber_;
		int y = previousShoot.columnNumber_;

		if (x > 0)
		{
			this->enemyField_->array[x-1][y].cellstate_ = MISSED;
			if (y>0)
				this->enemyField_->array[x-1][y-1].cellstate_ = MISSED;
			if (y<9)
				this->enemyField_->array[x-1][y+1].cellstate_ = MISSED;
		}

		if (x < 9 )
		{
			this->enemyField_->array[x+1][y].cellstate_ = MISSED;
			if (y>0)
				this->enemyField_->array[x+1][y-1].cellstate_ = MISSED;
			if (y<9)
				this->enemyField_->array[x+1][y+1].cellstate_ = MISSED;
		}

		if (y > 0)
		{
			this->enemyField_->array[x][y-1].cellstate_ = MISSED;
			
		}

		if (y < 9)
		{
			this->enemyField_->array[x][y+1].cellstate_ = MISSED;
			
		}
	}
}