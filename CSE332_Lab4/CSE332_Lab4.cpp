//File's name: CSE332_Lab4.cpp
//Authors: Yang Ye     ye@go.wustl.edu 
//         Yilong Hu   hu.yilong@wustl.edu
//         Chao Zhang  zcvictory0329@gmail.com
//Summary: The CSE332_Lab3.cpp defines the entry point for the console application.

#include "stdafx.h"
#include <ctype.h>
#include "GameBase.h"

enum length_of_argc{lower_range=1, upper_range=5};

using namespace std;

//usage funtion tell the user how to entry games. Also, you can type -h for help.
void usage(string proName){
	cout <<"usage:"<<proName<<".exe"<<" arg1 arg2 arg3 " <<
		   "or type"<<proName<<" -h for help";
}

//This funtion checks whether an input string is an integer or not. This integer could be negative and position.
//By doing this, we can check the input for magicsquare game whether it is valid.
bool is_number(char* s)
{
	int length = 0;
	string str(s);
	if(s[0] == '-'){
		for(unsigned int i = 1; i < str.length(); i++){
			if(!isdigit(s[i])){
			return false;
			}
		}	
	}
	else
	{
		for(unsigned  int i = 0; i < str.length(); i++){
			if(!isdigit(s[i])){
				return false;
			}
		}
	}
	return true;
}


//Here we first check the argument inputs, if all the inputs are valid, then we create a gamebase object point, then the gamebase
//pointer will call the either NineAlmonds or MagicSqure based on your inputs. Moreover, if you give a invalid input, we will teach you how to
//give the correct commands. You can type -h for help. The last thing in main function is to catch any error or user type quit during the game.
//If you quit the game, or any other execprtion occurs during the game, the game will terminate and tells you what just happened.
int main(int argc , char *argv[]){
	int result;
	if((lower_range < argc) && (argc < upper_range)){
		switch (argc)
		{
		case 2:
			if(strcmp(argv[1],"NineAlmonds") && strcmp(argv[1],"MagicSquare") && strcmp(argv[1],"-h")){
				usage(argv[0]);
				return wrongGameName;
			}
			if(!strcmp(argv[1],"-h")){
				cout << "usage:"<<argv[0]<<" arg1 arg2 arg3" << "\n" <<endl;
				cout <<"arg1  -	   Name of the games: NineAlmonds or MagicSquare or Reversi \n\t    e.g . "<<argv[0]<<" NineAlmonds" << "\n" << endl;
				cout <<"arg2  -    In MagicSquare, You can choose the size of the game board in. \n\t    e.g" <<argv[0]<<" MagicSquare 6\n" << endl;
				cout <<"           In Reversi, argv2 is required to be the black gamepiece player's name \n\t    e.g "<<argv[0]<<" Reversi Bob Mike\n"<<endl;
				cout <<"arg3  -	   In MagicSquare, You can choose the size of the game board and the starting number. \n\t    e.g "<<argv[0]<<" MagicSquare 6 -2\n" << endl;
				cout <<"           In Reversi, argv3 is required to be the white gamepiece player's name \n\t    e.g "<<argv[0]<<" Reversi Bob Mike\n"<<endl;
				return success;
			}
			break;
		case 3:
			if(strcmp(argv[1],"MagicSquare") || !is_number(argv[2])){
				usage(argv[0]);
				return fail;
			}
			break;
		case 4:
			if((strcmp(argv[1],"MagicSquare") || !is_number(argv[2]) || !is_number(argv[3])) && strcmp(argv[1],"Reversi")){
				usage(argv[0]);
				return fail;
			}
			break;
		}
		//GameBase *myGame = 0;
		try
		{
			GameBase::objAdReturn(argc, argv);
			//myGame=myGame->objAdReturn(argc,argv);
		}
		//make sure to catch the bad_alloc exception that might be thrown 
		//by the new operator if it fails to allocate memory.
		catch(bad_alloc)
		{
			cout<<"bad_alloc caught:"<<endl;
			return bad_Alloc;
		}
		catch(...)
		{
			cout<<"Other exceptions"<<endl;
			return other_exception;
		}
		if(GameBase::instance()!=nullptr) //make sure that if a game object was allocated 
		{	
			try
			{
				result=GameBase::instance()->play();
			}
			catch(int)
			{
				cout<<"Successfully quit!"<<endl;
				return magicsquare_user_quit;

			}
			catch(...)
			{
				cout<<"Other exceptions"<<endl;
				return other_exception;
			}
			if(result == ninealmonds_user_quit)
			{
				return ninealmonds_user_quit;
			}
			else if(result == stalemateOccured)
			{ 
				return stalemateOccured;
			}
			else if(result == magicsquare_user_quit)
			{
				return magicsquare_user_quit;
			}
			else if(result == reversi_user_quit)
			{
			    return reversi_user_quit;
			}
			else if(result == shared_exception)
			{
				return shared_exception;
			}
			return success;
		}
		else
			return fail;
	}
	else if(argc == 1)
	{
		usage(argv[0]);
		return not_enough_input;
	}
	else
	{
		usage(argv[0]);
		return too_many_input;
	}
}

