//File's name: GameBase.cpp
//Authors: Yang Ye    ye@go.wustl.edu  
//         Yilong Hu  hu.yilong@go.wustl.edu 
//         Chao Zhang zcvictory0329@gmail.com
//Summary: The GameBase.cpp defines the public member functions.

#include "stdafx.h"
#include "GameBase.h"
#include "MagicSquareGame.h"
#include "NineAlmondsGame.h"
#include "ReversiGame.h"
#include <memory>
//initialize the shared_ptr with nullptr. 
shared_ptr <GameBase> ptr = nullptr;

//Returns a shared smart pointer to the game base class
shared_ptr <GameBase> GameBase::instance()
{
	if (ptr != nullptr)
		return ptr;
	else
		throw shared_exception;
}

//This funtion defines which game user wants to play, then our gamebase object will call them based on the user's input, and return
//a gamebase point which points to the actual game object.
void GameBase::objAdReturn(int argc, char *argv[]){
	if(ptr == nullptr)
	{
		if ((argc == 2) && !strcmp(argv[1], "NineAlmonds")){
			ifstream gameFile;
			gameFile.open("NineAlmonds.txt");
			ptr = make_shared<NineAlmondsGame>(gameFile);
		}

		else if ((argc == 2) && !strcmp(argv[1], "MagicSquare")){
			ifstream gameFile;
			gameFile.open("MagicSquare.txt");
			ptr = (make_shared<MagicSquareGame>(gameFile));
		}

		else if ((argc == 3) && !strcmp(argv[1], "MagicSquare")){
			ifstream gameFile;
			gameFile.open("MagicSquare.txt");
			ptr = (make_shared<MagicSquareGame>(atoi(argv[2]),gameFile));
		}

		else if ((argc == 4) && !strcmp(argv[1], "MagicSquare")){
			ifstream gameFile;
			gameFile.open("MagicSquare.txt");
			ptr = (make_shared<MagicSquareGame>(atoi(argv[2]), atoi(argv[3]),gameFile));
		}
		else if((argc == 4) && !strcmp(argv[1], "Reversi")){
			ifstream gameFile;
			gameFile.open("Reversi.txt");
			ptr = (make_shared<ReversiGame>(argv[2],argv[3],gameFile));
		}
	}

	else{
		throw shared_exception;
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
		else if(game_status == reversi_user_quit)
		{
			cout << "\nReversi Game quits." <<endl;
			return reversi_user_quit;
		}
		else if(game_status == invalidMove){
			cout <<"You move is invalid, please try another move"<<endl;
		}
		else if(game_status == success){
			NumofTurn++;
		}
	}
	if((*this).GameName == "NineAlmonds"){
		if(this->done()){
			cout << "Win! You used " << NumofTurn << " turns" <<endl;
			return success;
		}
		else{
			cout << "Stalemate! You used " <<NumofTurn << " turns" <<endl;
			return stalemateOccured;
		}
	}
	else if((*this).GameName == "MagicSquare"){
		if(this->done()){
			cout << " You Win!"<<endl;
			return success;
		}
		else{
			cout << "Stalemate!"<<endl;
			return stalemateOccured;
		}
	}
	return success;
}