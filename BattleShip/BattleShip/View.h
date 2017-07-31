#ifndef View_H
#define View_H

#include<windows.h>
#include <iostream>
#include<conio.h>
#include<clocale>
#include<stdlib.h>
#include<ctime>
#include<iomanip>
#include<cmath>
#include<stdio.h>


#include "Observer.h"
#include "Field.h"


using namespace std;


enum ConsoleColor{Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White};


class View : public Observer
{
private:
	    Field* userField_;
		Field* computerField_;
		void SetColor (ConsoleColor text, ConsoleColor background);
		void PrintUserField (const Field & field);
		void PrintComputerField (const Field & field);
public: 
		View ();
		View (Field * userField, Field * computerField);
		~View ();
		void Update () override;
		void Draw ();

};

#endif 