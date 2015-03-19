
/*
File name:gameboard.cpp

Author:Hu Yilong

E-mail Address: hu.yilong@wustl.edu

Summary: This file includes a function named extractGame which will extract the strings from file to the dimensions of game board
and a function named readPieces which will read coordinations and information of game pieces from the file.
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
//read dimensions of game board from the file
int extractGame( ifstream &ifs, unsigned int &width, unsigned int &height)//extract the strings from file to the dimensions of game board
{
	string container; //read string from the file into container
	if(getline(ifs,container))//successfully read the line
	{
		istringstream iss (container);
		if( iss >> width && iss >> height)//extract well formed line into dimensions for game board
			return extractsuccess;
		else//cannot successfully extract dimensions because of the line is not well formed
			return extractfailure;
	}
	else//cannot successfully read line from the file
		return readfailure;
}

//read coordinations and information of game pieces from the file
int readPieces( ifstream &ifs, vector<game_piece> &gamespace, unsigned int width, unsigned int height)
{
	string container; //read string from the file into container
	string colorstr, namestr, printstr;
	unsigned int x=0, y=0;//the coordinations of game pieces
	int flag=nowellformed;//set a flag 
	while(getline(ifs,container))//successfully read the line
	{
		istringstream iss (container);//wrap string in a stream
		if(iss>>colorstr && iss>>namestr && iss>>printstr && iss >> x && iss >> y)
		{
			//extract well formed line into the different information of game pieces
			if(x < width && y < height && stringToEnum(colorstr)!=invalidcolor)
			{
				flag=haswellformed;//at least has one well-formed line
				gamespace[width*y+x].color = stringToEnum(colorstr);
				gamespace[width*y+x].name = namestr;
				gamespace[width*y+x].printout = printstr;
			}
		}
	}
	return flag;
}




