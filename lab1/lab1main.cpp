
/*
File name:lab1main.cpp

Author:Hu Yilong

E-mail Address: hu.yilong@wustl.edu

Summary: This file includes main function of the whole program and it will
call different functions defined in other cpp file. In addition, it will
check each return values of the functions it called and examine them.
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

int main(int argc, char* argv[])
{
	string hint("lab1 file.txt");
	if(argc!=2)//check that exactly one argument was passed to the program (in addition to the program's name)
	{
		message(argv[proname], hint);
	}
	else//the number of arguments is correct 
	{
		ifstream ifs; 
		ifs.open(argv[filename]);//open an input file stream
		if(!ifs.is_open())//the file cannot be opened successfully
		{
			cout<<"The file cannot be opened successfully"<<endl;
			return filefailure;
		}
		else//the file is opened successfully
		{
			//one for the horizontal extent and one for the vertical extent of a game board
			unsigned int width, height;
			int result = extractGame( ifs, width, height);
			while(result==extractfailure)//able to read a line but could not extract the dimensions from that line
			{
				int result = extractGame( ifs, width, height);
				if(result==extractsuccess)//returns success or a value indicating that it could not read a line from the file
				{
					break;
				}
				else if (result==readfailure)//loop until it is the last line in the file but still not a valid dimension
				{
					cout<<"never able to extract board dimensions from the file."<<endl;
					return readfailure;
			     } 
			}
			//the dimensions of game board is successfully extracted out
			vector<game_piece> gamespace;//declare a vector of game pieces
			for(unsigned int i=0; i< width*height; ++i)//for each position on the board
			{
				game_piece piece;
				piece.color = nocolor; //initialize color with nocolor
				piece.name= ""; //initialize name with nothing
				piece.printout= " ";//initialize printout with an empty string
				gamespace.push_back(piece);// repeatedly push back a game piece that represents an empty square on the board
			}
			
			int result2 = readPieces( ifs, gamespace, width, height);
			if(result2==nowellformed)
			{
				cout<<"never able to extract the coordinations of game piece from the file"<<endl;
				return nowellformed;
			}
			else//the result2 = haswellformed and the program goes on
			{
			   //vector<game_piece> const& const_space = gamespace;//send a non-const value into a const parameter of another function
               int result3 = printGame(gamespace, width, height);
			   if(result3==printfailure)
			   {
				   cout<<"print failure: the size of the vector does not match the dimensions of the game board that were passed in"<<endl;
				   return printfailure; // return a value indicating the failure of printing out
			   }
			   else
			   {
				   ifs.close ();
				   //prints out every checker on the board and those which are adjacent to it
				   extraCredit(gamespace, width ,height);
				   return printsuccess; // return a value indicating the succes of printing out
			   }
			}
		}
	}
}
