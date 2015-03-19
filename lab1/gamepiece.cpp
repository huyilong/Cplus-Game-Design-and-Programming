
/*
File name:gamepiece.cpp

Author:Hu Yilong

E-mail Address: hu.yilong@wustl.edu

Summary: This file includes a function named enumToString which may convert a value in piece_color
into a string and return it, a function named stringToEnum which may convert a string into a 
piece_color type value and return it.
*/

#include "stdafx.h"
#include "lab1header.h"
#include "pieceheader.h"
#include "boardheader.h"
#include <iostream>
#include <vector>
#include <string>
#include<sstream>
#include<istream>
#include<fstream>

using namespace std;

// read by value and return a string representing the color in lowercase
string enumToString(int value)
{
	switch(value)
	{
	   case nocolor:
		   {
			   return "nocolor";
			   break;
		   }
	   case black:
		   {
				return  "black";
		     	break;
		   }
	   case white:
		   {
			   return "white";
			   break;
		   }
	   case red:
		   {
			   return "red";
			   break;
		   }
	   default:
				return "novalidcolor";
	}	
}


// read by string and return a piece_color value
int stringToEnum(string str)
{
	if(str==" ")//conver empty string into enumeration label "nocolor"
		{
			return nocolor;
		}
	else if(str=="red")//conver string "red" into enumeration label "red"
		{ 
			return red;
		}
	else if(str=="black")//conver string "black" into enumeration label "black"
		{
			return black;
		}
	else if(str=="white")//conver string "white" into enumeration label "white"
		{
			return white;
		}
	else //not a valid string
		{
			return invalidcolor;
		}

}