//File's name:GameBase.h  
//Authors: Yang Ye    ye@go.wustl.edu  
//		   Yilong Hu  hu.yilong@go.wustl.edu  
//         Chao Zhang zcvictory0329@gmail.com
//Summary: The GameBase.h declares protected members, public members and enum type variables. The public members functions contain constructures, destructures, some pure virtual functions.

#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "stdafx.h"
#include <vector>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <memory>

enum return_value{success, fail, wrongGameName, too_many_input, not_enough_input, unable_to_read_coordinate, invalidMove,stalemateOccured, ninealmonds_user_quit, magicsquare_user_quit, reversi_user_quit, bad_Alloc, shared_exception, unknown_exception, other_exception, one_player_done, one_turn_done,file_reading_failed,file_writing_failed};

using namespace std;

class GameBase{
protected:
	int width;
	int height;
	string GameName;
	unsigned int longestPieceLength;
	vector<vector<string>> gameState;
public:
	GameBase() {}
	GameBase(int x, int y): width(x), height(y){}
	~GameBase() {}
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int prompt(unsigned int &fir, unsigned int &sec) = 0;
	virtual int prompt(int &inputInt) = 0;
	virtual int turn() = 0;
	virtual int play();
	static shared_ptr<GameBase> instance();
	static void objAdReturn(int argc, char *argv[]); 
private:
	//prevent copy constructor
	GameBase(const GameBase &);
	//prevent copy assignment operator 
	GameBase & GameBase :: operator = (const GameBase &);
	//prevent move constructor
	GameBase (GameBase &&); 
	//prevent move assignment operator
	GameBase & GameBase :: operator = (GameBase &&);
};

#endif
