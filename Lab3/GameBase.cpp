//File's name: GameBase.cpp
//Authors: Yang Ye    ye@go.wustl.edu  
//         Yilong Hu  hu.yilong@go.wustl.edu 
//         Chao Zhang zcvictory0329@gmail.com
//Summary: The GameBase.cpp defines the public member functions.

#include "stdafx.h"
#include "GameBase.h"
#include "MagicSquareGame.h"
#include "NineAlmondsGame.h"

enum return_value{success, fail, wrongGameName, too_many_input, not_enough_input, unable_to_read_coordinate, invalidMove,stalemateOccured, ninealmonds_user_quit, magicsquare_user_quit, bad_Alloc, unknown_exception, other_exception};

//This funtion defines which game user wants to play, then our gamebase object will call them based on the user's input, and return
//a gamebase point which points to the actual game object.
GameBase* GameBase::objAdReturn(int argc, char *argv[]){
	GameBase *objPtr;
	//JZ: hard-coded constants here, and this could definitely have been
	//amended via the use of enums
	if ((argc == 2) && !strcmp(argv[1], "NineAlmonds")){
		objPtr = new NineAlmondsGame;
		return objPtr;
	}

	else if ((argc == 2) && !strcmp(argv[1], "MagicSquare")){
		objPtr = new MagicSquareGame;
		return objPtr;
	}

	else if ((argc == 3) && !strcmp(argv[1], "MagicSquare")){
		objPtr = new MagicSquareGame(atoi(argv[2]));
		return objPtr;
	}

	else if ((argc == 4) && !strcmp(argv[1], "MagicSquare")){
		objPtr = new MagicSquareGame(atoi(argv[2]),atoi(argv[3]));
		return objPtr;
	}

	else{
		objPtr=nullptr;
		return objPtr;
	}
}


//This function outputs game board and call done() and stalemate() functions. At last it will output the all turns you need if you win
//or say that you quit at some turn or try another move if you input invalid or output the all turns you need if you stalemate.
int GameBase::play(){
	int NumofTurn = 0;
	int game_status;
	this->print();
	while(!this->done() && !this->stalemate()){
		try
		{
			game_status = this->turn();
		}
		catch(int)
		{
			throw (int)magicsquare_user_quit;
		}
		if(game_status == ninealmonds_user_quit){
			cout << "User quits at turn " << NumofTurn <<endl;
			return ninealmonds_user_quit;
		}
		else if(game_status == invalidMove){
			cout <<"You move is invalid, please try another move"<<endl;
		}
		else if(game_status == success){
			NumofTurn++;
		}
	}
	if(this->done()){
		cout << "Win! You used " << NumofTurn << " turns" <<endl;
		return success;
	}
	else{
		cout << "Stalemate! You used " <<NumofTurn << " turns" <<endl;
		return stalemateOccured;
	}
}