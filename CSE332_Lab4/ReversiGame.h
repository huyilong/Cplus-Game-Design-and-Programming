//File's name: ReversiGame.h  
//Authors: Yang Ye    ye@go.wustl.edu  
//         Yilong Hu  hu.yilong@go.wustl.edu  
//         Chao Zhang zcvictory0329@gmail.com
//Summary: The ReversiGame.h declares private members and public members. The public members functions contain constructors, destructors, some virtual functions.
#ifndef REVERSIGAME_H
#define REVERSIGAME_H
#include "stdafx.h"
#include "GameBase.h"


class ReversiGame : public GameBase
{
	friend ostream &operator<<(ostream &out, const ReversiGame &game);
private:
    string black_player, white_player;
    string current_player;
	//prevent copy constructor
	ReversiGame(const ReversiGame &);
	//prevent copy assignment operator 
	ReversiGame & ReversiGame :: operator = (const ReversiGame &);
	//prevent move constructor
	ReversiGame (ReversiGame &&); 
	//prevent move assignment operator
	ReversiGame & ReversiGame :: operator = (ReversiGame &&);


public:
	ReversiGame(string black_player, string white_player,ifstream& gameFile);
    ~ReversiGame(){};
    
    virtual void print();
    virtual bool done();
    virtual bool stalemate();
    virtual int prompt(unsigned int &fir, unsigned int &sec);
    virtual int prompt(int &inputInt);
    virtual int turn();
    
    bool hasValidSquare();
	bool checkValid(string current, string opposite);
	bool moveisValid(string current,string opposite, unsigned int player_destination_x, unsigned int player_destination_y);
};
#endif