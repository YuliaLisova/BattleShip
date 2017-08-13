#include "Field.h"

Field ::Field()
	{
		for (int i = 0; i < size_; i ++)
	{
		for (int j = 0; j < size_; j ++)
		{
			array[i][j].cellPosition_ = EMPTY;
			array[i][j].cellstate_ = CLEAN;
			array[i][j].rowNumber_ = i;
			array[i][j].columnNumber_ =j;

		
	}
	}
	}

Field ::~Field()
{
	
}

void Field :: ClearField ()
{
  for (int i = 0; i < size_; i++)
	{
			for (int j = 0; j < size_; j++)
			{
				array[i][j].cellPosition_ = EMPTY;
			}
	}
}