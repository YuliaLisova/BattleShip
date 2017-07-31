
#include "View.h"

View ::View ()
{

}

View ::View (Field * userField, Field * computerField)
{
	this->userField_ = userField;
	this ->computerField_ = computerField;
	userField->AddObserver (this);

	computerField->AddObserver (this);
}

View :: ~View ()
{

}
void  View :: SetColor(ConsoleColor text, ConsoleColor background)
{ 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void View :: PrintUserField (const Field & field)
{
	cout<<"Your field"<<endl;
	cout<<endl;
	cout.width(2);
		cout<<" ";
		
	for (int i = 65 ; i<= 74; i++)
	{
		
		cout.width(2);
		cout<<static_cast <char> (i);
	}
	cout<<endl;
	for (int i =0; i<10; i++)
	{
		
		cout<<setw(2)<<i+1;
		for (int j = 0; j<10; j++)
		{
			cout.width(2);
			if (field.array[i][j].cellPosition_ == EMPTY)
			{
				if (field.array[i][j].cellstate_ == MISSED)
				{
                 SetColor(Yellow, Black);
				 cout<<"O";
				}
				else cout <<".";

				SetColor(White, Black);
			}
			else if (field.array[i][j].cellPosition_ == DECK)

			{

				 if (field.array[i][j].cellstate_ == KILLED)
			  {
				   SetColor(Black, Red);
				  cout <<'X';
			  }
			  
			  else if (field.array[i][j].cellstate_ == INJURED)
			  {
				  SetColor(Black, Yellow);
				  cout <<'X';
			  }
			  
			  else 
				  {SetColor(Green, Green);
			  cout<<" ";}
				SetColor(White, Black);
			
			}
			else if (field.array[i][j].cellPosition_ == BORDER)
			{
				if (field.array[i][j].cellstate_ == MISSED)
				{
					SetColor(Yellow, Black);
				cout <<"O";
				}
				else
				cout <<".";

				SetColor(White, Black);
			}
		}
		cout<<endl;
	}

	cout<<endl<<"------------------------";
}


void View :: PrintComputerField (const Field & field)
{
	cout<<endl<<"Computer's field"<<endl;
	cout.width(2);
		cout<<" ";
	for (int i = 65 ; i<= 74; i++)
	{cout.width(2);
		cout<<static_cast <char> (i);
	}
	cout<<endl;
	
	for (int i = 0; i< 10; i++)
	{
		cout<<setw(2)<<i+1;
		for (int j = 0; j <10; j ++)
		
		{
		cout.width(2);
		if (field.array[i][j].cellPosition_ == DECK)
		  {
			  //SetColor(Yellow, Red);
				  
			  if (field.array[i][j].cellstate_ == CLEAN)
				  cout <<".";
			  else if (field.array[i][j].cellstate_ == INJURED)
			  {
				  SetColor(Black, Yellow);
				  cout <<"x";
			  }
			  else if (field.array[i][j].cellstate_ == KILLED)
			  {
				  SetColor(Black, Red);
				  cout <<"Z";
			  }
		  }
		else 
		{
			 SetColor(Yellow, Black);
			if (field.array[i][j].cellstate_ == MISSED)
				cout <<"0";
			else cout <<".";
		}

		}

		 SetColor(White, Black);
		cout<<endl;
	}
}

void View :: Draw ()
{
	system("cls");
	PrintUserField(*this->userField_);
	PrintComputerField(*this->computerField_);
}

void View ::Update ()
{
	Draw();
}