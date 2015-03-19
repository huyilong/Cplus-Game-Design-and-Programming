/*
File name:lab1header.h

Author:Hu Yilong

E-mail Address: hu.yilong@wustl.edu

Summary: This file includes the declarations of functions named message, toLowerCase,
extractGame, printGame and extraCredit. And the enumerations named RetVal and Arguments.
*/

#include <iostream>
#include<sstream>
#include<istream>
#include<fstream>
#include<string>
#include<vector>
#include "boardheader.h"

//create an enumeration for different return values of functions
enum RetVal{
	usagefailure,
	readfailure,
	extractsuccess,
	filefailure,
	extractfailure,
	haswellformed,
	nowellformed,
	printsuccess,
	printfailure
};

//create an enumeration for different index of the arguments
enum Arguments { 
	proname,//the subscript of program's name stored in argv[]
	filename,//the subscript of file's name stored in argv[]
    requirenum//the correct number of the commands typed by user
};

//print out the usage message to the user
int message(string, string);
//receive a string and convert it into lowercase
string toLowerCase(string);
//read dimensions of game board from the file
int extractGame(ifstream &, unsigned int &, unsigned int &);
//print out all the checkers on the board
int printGame(const vector<game_piece> &, unsigned int, unsigned int);
//prints out every checker on the board and those which are adjacent to it
void extraCredit(const vector<game_piece> &, unsigned int, unsigned int);


