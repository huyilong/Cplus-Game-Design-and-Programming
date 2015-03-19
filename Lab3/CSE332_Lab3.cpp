//File's name: CSE332_Lab3.cpp
//Authors: Yang Ye     ye@go.wustl.edu 
//         Yilong Hu   hu.yilong@wustl.edu
//         Chao Zhang  zcvictory0329@gmail.com
//Summary: The CSE332_Lab3.cpp defines the entry point for the console application.

#include "stdafx.h"
#include <ctype.h>
#include "GameBase.h"

//JZ: these enums could/possibly ought to be part of a CSE332_Lab3.h 
enum return_value{success, fail, wrongGameName, too_many_input, not_enough_input, unable_to_read_coordinate, invalidMove,stalemateOccured, ninealmonds_user_quit, magicsquare_user_quit, bad_Alloc, unknown_exception, other_exception};
enum length_of_argc{lower_range=1, upper_range=5};

using namespace std;

//usage funtion tell the user how to entry games. Also, you can type -h for help.
void usage(){
	cout <<"usage:./CSE332_Lab3 arg1 arg2 arg3 " <<
		   "or type ./CSE332_Lab3 -h for help";
	//JZ: hey! your usage message should *not* have the exe name hard-coded;
	//it should determine it based on argv[0].
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


//Here we firstly check the argument inputs, if all the inputs are valid, then we create a gamebase object point, then the gamebase
//pointer will call the either NineAlmonds or MagicSqure based on your inputs. Moreover, if you give a invalid input, we will teach you how to
//give the correct commands. You can type -h for help. The last thing in main function is to catch any error or user type quit during the game.
//If you quit the game, or any other execprtion occurs during the game, the game will terminate and tells you what just happened.
int main(int argc , char *argv[]){
	int result;
	if((lower_range < argc) && (argc < upper_range)){
		switch (argc)
		{
			//JZ: by adding additional labels into length_of_argc you could've avoided these hard-coded
			//constants when trying to index the game name, arguments, etc.
		case 2:
			if(strcmp(argv[1],"NineAlmonds") && strcmp(argv[1],"MagicSquare")&& strcmp(argv[1],"-h")){
				usage();
				return wrongGameName;
			}
			if(!strcmp(argv[1],"-h")){
				cout << "usage:./CSE332_Lab3 arg1 arg2 arg3" << "\n" <<endl;
				cout <<"arg1  -	   Name of the games: NineAlmonds or MagicSquare \n\t    e.g ./CSE332_Lab3 NineAlmonds" << "\n" << endl;
				cout <<"arg2  -    (Optional) You can choose the size of the game board in MagicSquare \n\t    e.g ./CSE332_Lab3 MagicSquare 6"<<"\n" << endl;
				cout <<"arg3  -	   (Optional) You can choose the size of the game board and the starting number in MagicSquare \n\t    e.g ./CSE332_Lab3 MagicSquare 6 -2"<<"\n" << endl;
				return success;
			}
			break;
		case 3:
			if(strcmp(argv[1],"MagicSquare") || !is_number(argv[2])){
				usage();
				return fail;
			}
			break;
		case 4:
			if(strcmp(argv[1],"MagicSquare") || !is_number(argv[2]) || !is_number(argv[3])){
				usage();
				return fail;
			}
			break;
		}
		GameBase *myGame = 0;
		try
		{
			myGame=myGame->objAdReturn(argc,argv);
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
		//initialize a shared_ptr variable with the pointer that was returned by the static method
		GameBase *shared_ptr=myGame;
		if(shared_ptr!=0) //make sure that if a game object was allocated 
		{	
			try
			{
				result=shared_ptr->play();
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
			if(result==ninealmonds_user_quit)
			{
				return ninealmonds_user_quit;
			}
			delete shared_ptr; //the allocated object is also destroyed
			return success;
		}
		else
			return fail;
	}
	else if(argc == 1)	//JZ: note that this check could've benefited from the length_of_argc enum
	{
		usage();
		return not_enough_input;
	}
	else
	{
		usage();
		return too_many_input;
	}
}

