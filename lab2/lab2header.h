
/*
File name:lab2header.h

Author:Hu Yilong

E-mail Address: hu.yilong@wustl.edu

Summary: This file includes the declarations of a class named
single_player, which includes the core definitions of functions
and variables used in the nine almonds game, which include
done(), turn(), stalemate(), prompt(), continue_prompt(), and play().
There is also a definition of operator so that it can conveniently
print out the contents of game board for the program.
*/

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
//create an enumeration for different return values of functions
enum RetVal{
	finishgame,
	quitgame,
	stalemategame,
	promptsuccess,
	continue_promptsuccess,
	turnsuccess,
	turnfailure,
	usagefailure,
	illegalcase
};

//create an enumeration for different index of the arguments
enum Arguments {
	proname,//the subscript of program's name stored in argv[]
	filename,//the subscript of file's name stored in argv[]
	requirenum//the correct number of the commands typed by user
};

//create an enumeration for different colors of game pieces
enum piece_color{
	invalidcolor,
	nocolor,
	red,
	black,
	white,
	brown
};

//declare a struct for game pieces
struct game_piece {
	int color;
	string name;
	string printout;
};

// read by string and return a piece_color value
int stringToEnum(string);
//print out the usage message to the user
int message(string, string);
//game class
class single_player{

	friend ostream &operator << (ostream &out, const single_player &player);

private:
	vector<game_piece> gamespace;//declare a vector of game pieces
	int width,height;

	//declare and define the following functions inside the single_player class
public:
	//declarations of functions 
	bool done();
	bool stalemate();
	bool single_player::is_stalemate(const vector<game_piece> &gamespace, unsigned int width ,unsigned int height);
	int prompt(unsigned int & x_ , unsigned int & y_);
	int continue_prompt(unsigned int & x_ , unsigned int & y_);
	int turn();
	int play();

	//the default constructor of single_player class
	single_player::single_player(int width=5, int height=5)
	{
		this->width=width;
		this->height=height;
		for(int i=0; i< width*height; ++i)//for each position on the board
		{
			game_piece piece;
			piece.color = nocolor; //initialize color with nocolor
			piece.name= ""; //initialize name with nothing
			piece.printout= " ";//initialize printout with an empty string
			gamespace.push_back(piece);// repeatedly push back a game piece that represents an empty square on the board
		}
		for(int i=0; i< width*height; ++i)//the middle nine pieces are put on the board
		{
			if(i>=6&&i<=18&&i!=9&&i!=10&&i!=14&&i!=15)//the index is within the range of midlle nine pieces
			{
				gamespace[i].color = stringToEnum("brown");
				gamespace[i].name = "almond";
				gamespace[i].printout = 'A';
			}
		}
	}
};

// declare an insertion operator
ostream & operator<<(ostream &out, const single_player &player);

//when the number of commands typed in by user is wrong, print out the message and return fail
int message(string name, string hint);
// read by string and return a piece_color value
int stringToEnum(string str);

