//File's name:GameBase.h  
//Authors: Yang Ye    ye@go.wustl.edu  
//		   Yilong Hu  hu.yilong@go.wustl.edu  
//         Chao Zhang zcvictory0329@gmail.com
//Summary: The GameBase.h declares protected members, public members and enum type variables. The public members functions contain constructures, destructures, some pure virtual functions.

#ifndef GAMEBASE_H
#define GAMEBASE_H
#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class GameBase{
protected:
	int width;
	int height;
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
	GameBase *objAdReturn(int argc, char *argv[]); 
};

#endif
