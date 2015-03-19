
/*
File name:pieceheader.h

Author:Hu Yilong

E-mail Address: hu.yilong@wustl.edu

Summary: This file includes the declarations of functions named enumToString and
stringToEnum and the enumeration named piece_color and a struct named game_piece.
*/

#include "stdafx.h"
#include <string>


//create an enumeration for different colors of game pieces
enum piece_color{
	invalidcolor,
	nocolor,
	red,
	black,
	white
};

//declare a struct for game pieces
struct game_piece {
  int color;
  string name;
  string printout;
};

// read by value and return a string representing the color in lowercase
string enumToString(int );
// read by string and return a piece_color value
int stringToEnum(string);
