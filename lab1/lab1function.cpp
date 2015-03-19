
/*
File name:lab1function.cpp

Author:Hu Yilong

E-mail Address: hu.yilong@wustl.edu

Summary: This file includes a function named message which may print out a helpful message to users when they type in wrong commands
and a function named toLowerCase which converts a string into lowercase and a function to print out the whole board and a function
which will print out each checker on the board and its neighboring checkers.
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

int message(string name, string hint)//when the number of commands typed in by user is wrong, print out the message and return fail
{
	cout<<"program name:"<<name<<"usage:"<<hint<<endl;
	return usagefailure;//return a value indicating the failure of command from user
}

string toLowerCase(string tolower)//receive a string and convert it into lowercase
{
	char* index= &tolower.at(0);
	while(index!='\0') //loop until processing to the end of the string
	{
		if(*index<='Z' && *index>='A')//check out if the character is uppercase
		{
          *index = *index-('Z'-'z');//convert the uppercase letter into lowercase
		} 
		index++; //check next character of the string
	}

    return tolower;//return the string which has been converted to lowercace
}

int printGame( const vector<game_piece> &gamespace, unsigned int width ,unsigned int height)//print out all the checkers on the board
{
	if( gamespace.size() != width*height )//the size of the vector does not match the dimensions of the game board that were passed in
	{
		cout<< gamespace.size()<<endl;
		return printfailure; // return a value indicating the failure of printing out
	}

	else//print ou the game board and the game pieces on it
	{

		for(int y_ = static_cast<int>((height-1)); y_ >= 0; --y_)//start printing out from the upper side of the whole game board
		{
			for(int x_=0; x_ < static_cast<int>(width); ++x_)//start printing out from the left side of the whole game board
			{
				cout<<gamespace[width*y_+x_].printout; //once print out one line
			}
		
			cout<<endl; //begin to print from next line
		}
		return printsuccess; // return a value indicating the succes of printing out
	}
}

//prints out every checker on the board and those which are adjacent to it
void extraCredit( const vector<game_piece> &gamespace, unsigned int width ,unsigned int height)
{
	int flag=0;
	for(int i=0; i<static_cast<int>(gamespace.size());++i)
	{
		if(gamespace[i].color!=nocolor)//for positions that have chess
		{
			cout<<(i%width)<<","<<(i/width)<<" "<< enumToString(gamespace[i].color) <<" "<<gamespace[i].name<<": ";
			int left=i-1, right=i+1, down=i-width, up=i+width, rightup=i+width+1, rightdown=i-width+1, leftup=i+width-1, leftdown=i-width-1;
			//the left neighbor position is within the board and has a chess in it and it is in the same row with chess[i]
			if(left>=0&&left<static_cast<int>(gamespace.size())&&gamespace[left].color!=nocolor&&(left/width)==(i/width))//the neighbor position is within the board and has a chess in it
			{
				cout<<(left%width)<<","<<(left/width)<<" "<< enumToString(gamespace[left].color) <<" "<<gamespace[left].name<<"; ";
				flag=1;
			}
			//the right neighbor position is within the board and has a chess in it and it is in the same row with chess[i]
			if(right>=0&&right<static_cast<int>(gamespace.size())&&gamespace[right].color!=nocolor&&(right/width)==(i/width))
			{
				cout<<(right%width)<<","<<(right/width)<<" "<< enumToString(gamespace[right].color) <<" "<<gamespace[right].name<<"; ";
				flag=1;
			}
			//the upper neighbor position is within the board and has a chess in it
			if(up>=0&&up<static_cast<int>(gamespace.size())&&gamespace[up].color!=nocolor)
			{
				cout<<(up%width)<<","<<(up/width)<<" "<< enumToString(gamespace[up].color) <<" "<<gamespace[up].name<<"; ";
				flag=1;
			}
			//the downside neighbor position is within the board and has a chess in it
			if(down>=0&&down<static_cast<int>(gamespace.size())&&gamespace[down].color!=nocolor)
			{
				cout<<(down%width)<<","<<(down/width)<<" "<< enumToString(gamespace[down].color) <<" "<<gamespace[down].name<<"; ";
				flag=1;
			}
			//the rightup neighbor position is within the board and has a chess in it
			if(rightup>=0&&rightup<static_cast<int>(gamespace.size())&&gamespace[rightup].color!=nocolor)
			{
				cout<<(rightup%width)<<","<<(rightup/width)<<" "<< enumToString(gamespace[rightup].color) <<" "<<gamespace[rightup].name<<"; ";
				flag=1;
			}
			//the rightdown neighbor position is within the board and has a chess in it
			if(rightdown>=0&&rightdown<static_cast<int>(gamespace.size())&&gamespace[rightdown].color!=nocolor)
			{
				cout<<(rightdown%width)<<","<<(rightdown/width)<<" "<< enumToString(gamespace[rightdown].color) <<" "<<gamespace[rightdown].name<<"; ";
				flag=1;
			}
			//the leftup neighbor position is within the board and has a chess in it
			if(leftup>=0&&leftup<static_cast<int>(gamespace.size())&&gamespace[leftup].color!=nocolor)
			{
				cout<<(leftup%width)<<","<<(leftup/width)<<" "<< enumToString(gamespace[leftup].color) <<" "<<gamespace[leftup].name<<"; ";
				flag=1;
			}
			//the leftdown neighbor position is within the board and has a chess in it
			if(leftdown>=0&&leftdown<static_cast<int>(gamespace.size())&&gamespace[leftdown].color!=nocolor)
			{
				cout<<(leftdown%width)<<","<<(leftdown/width)<<" "<< enumToString(gamespace[leftdown].color) <<" "<<gamespace[leftdown].name<<"; ";
				flag=1;
			}
			//there is no checkers neighboring the current checker
			if(flag==0)
			{
				cout<<"has no neighboring checkers";
			}
			cout<<endl;//print out next chess on the board from a new line
			flag=0;//reset the flag
		}
	}
}
