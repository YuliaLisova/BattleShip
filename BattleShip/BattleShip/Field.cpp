#include "Field.h"

Field ::Field()
	{
		for (int i = 0; i<10; i ++)
	{
		for (int j = 0; j<10; j ++)
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
  for (int i=0; i<10; i++)
	{
			for (int j=0; j<10; j++)
			{
				array[i][j].cellPosition_ = EMPTY;
			}
	}
}