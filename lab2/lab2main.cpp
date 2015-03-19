
/*
File name:lab2main.cpp

Author:Hu Yilong

E-mail Address: hu.yilong@wustl.edu

Summary: This file includes main function of the whole program and it will
call different functions defined in other cpp file or header file. In addition,
it will examine whether the input from user is appropriate and prompt user with
correct usage of this nine almonds program. The main function will return different
unique values according to the different result of function play.

Annotation: Based on my designment, if user types in wrong commands in a continuous turn, the program will ask the user to
retype in all the two pairs of coordinates, i.e. it will jump out of the former turn and begin a totally new turn with its
corresponding track.

User-friendly Design: In my program, if the user types in wrong commands, the program will examine the reason why the command
is not correct, i.e. whether it is caused by the wrong beginning position, or there is no middle almond between the beginning
and the destination, or there is already an almond existing in the desitination. Furthermore, the program will inform the user
of the different reasons for the failure of making a valid move and ask the user to retype in the two pairs of coordinates.
*/

#include "stdafx.h"
#include "lab2header.h"
#include <iostream>
#include <vector>
#include <string>
#include<sstream>
#include<istream>
#include<fstream>
using namespace std;

int main(int argc, char* argv[])
{
    string name = "NineAlmonds";
    int mainresult;
	//pointer check1 points to the first character of the correct name of the program
    char* check1= &name.at(0);
	//pointer check2 points to the first character of the name typed in by the user
    char* check2= argv[1];
    if(argc==requirenum)//if there is only one command typed by the user
    {
        for(unsigned int i=0;i<name.length();i++)//check the command typed by user with the correct program name
        {
            if(*check2!=*check1)
                return message(argv[0],"NineAlmonds");
            //increase the pointer and check up the next characters between two strings
			else
			{
				check1++;
				check2++;
			}
        }   
    }
    else//the number of commands is not correct
        return message(argv[0],"NineAlmonds");
    single_player player;
    mainresult=player.play();
    //the main function will return different unique values according to the different result of function play
    switch(mainresult)
    {
		//the user completes the game and return a success code (with value 0)
        case finishgame:
            return finishgame;
            break;
		//the game becomes a stalemate and return an unique value
        case stalemategame:
            return stalemategame;
            break;
		//the user quits the game and return an unique value
        case quitgame:
            return quitgame;
            break;
    }
    
}