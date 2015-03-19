//File's name: MagicSquareGame.h  
//Authors: Yang Ye    ye@go.wustl.edu  
//         Yilong Hu  hu.yilong@go.wustl.edu
//		   Chao Zhang zcvictory0329@gmail.com
//Summary: The MagicSquareGame.cpp defines public members funcions.

#include "stdafx.h"
#include "MagicSquareGame.h"
#include <algorithm>
#include <cmath>

//JZ: see other notes about this enum
enum return_value{success, fail, wrongGameName, too_many_input, not_enough_input, unable_to_read_coordinate, invalidMove,stalemateOccured, ninealmonds_user_quit, magicsquare_user_quit, bad_Alloc, unknown_exception, other_exception};

//This is a definition of insertion operator. The insertion operator can output the game board.
ostream &operator<<(ostream &out, const MagicSquareGame &game){
	for (int j = game.height-1; j >= 0; j--){
		out << j <<" ";
		for(int i = 0; i < game.width; i++){
			if(i == 0){
			out << setw(game.longestPieceLength - game.gameState[j][i].length()+1)<<game.gameState[j][i];
			}
			else{
			out << setw(game.longestPieceLength+1) << game.gameState[j][i];
			}
		}
		out << endl;
	}
	out << "X";
	//This line outputs the x-axe of the game board. And this part can print the board out by the maximum display string length stored by the base class.
	for(int i = 0; i < game.width; i ++)
		out << setw(game.longestPieceLength+1) << i;
	out << endl;

	//This part can print the Available pieces line blew the game board to indicate that what game pieces we can choose.
	out<<"Available pieces: ";//print out the updated available pieces list
	for(int i=0 ; i < static_cast<int>(game.availablePieces.size());i++){
		out<<game.availablePieces[i] << " ";
	}
	out<<endl;

	return out;
}

//This function defines a constructor. The default constructor shows that if you input nothing in the command line except game name, it will automatically defines that this game board is a 3x3 matrix and
//the game piece number begins from 1.
MagicSquareGame::MagicSquareGame(){
	width = 3;
	height = 3;
	int gameboardlength = width*height;
	longestPieceLength = 0;
	for(; gameboardlength!= 0; gameboardlength/=10, longestPieceLength++);
	startMin = 1;
	vector<string> row;
	for(int i = 0; i < height; i ++){
		for(int j = 0; j < width; j ++){
			row.push_back(" ");
		}
		gameState.push_back(row);
	}

	for(int i = 1; i <= width*height; i ++){
		availablePieces.push_back(i);
	}
}

//This function defines another constructon. The constructor defines the width and height from the input of command line.
//The game piece number begins from 1.
MagicSquareGame::MagicSquareGame(int size){
	width = size;
	height = size;
	int gameboardlength = width*height;
	longestPieceLength = 0;
	for(; gameboardlength!= 0; gameboardlength/=10, longestPieceLength++);
	startMin = 1;
	vector<string> row;
	for(int i = 0; i < height; i ++){
		for(int j = 0; j < width; j ++){
			row.push_back(" ");
		}
		gameState.push_back(row);
	}
	
	for(int i = 1; i <=size*size; i ++){
		availablePieces.push_back(i);
	}
}

//Theis function defines another construction. The constructor defines width and height from the input of command line.
//The game piece number begins the number you input.
MagicSquareGame::MagicSquareGame(int size, int min){
	width = size;
	height = size;
	startMin = min;
	int gameboardlength = width*height;
	longestPieceLength = 0;
	for(; gameboardlength!= 0; gameboardlength/=10, longestPieceLength++);
	vector<string> row;
	for(int i = 0; i < height; i ++){
		for(int j = 0; j < width; j ++){
			row.push_back(" ");
		}
		gameState.push_back(row);
	}
	if(startMin > 0){
		for(int i = startMin; i <=size*size+abs(startMin); i++){
			availablePieces.push_back(i);
		}
	}
	else{
		for(int i = startMin; i <=size*size-abs(startMin)-1; i++){
			availablePieces.push_back(i);
		}
	}
}

void MagicSquareGame::print()
{
   cout<<(*this)<<endl;
}

//The function makes a judgement that whether the sum of the integer values of the pieces along every diagonal, row, or column is the same or not. If right, return true, otherwise return false.
bool MagicSquareGame::done()
{
	if(this->boardisFull()){
		int ref=0,sum=0;
		for(int s=0; s<width; s++)
		{
			ref+=stoi(gameState[0][s]);
		}//set up the overall standard using the sum of first row

		//start from the first row with the first row's sum as reference
		for(int i=1; i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				sum+=stoi(gameState[i][j]);//every row's sum
			}
			if(sum!=ref)//two rows' sum are equal,continue to check the next row
				return false; 
			sum=0;//reset the sum for calculating the sum of next row
		}

		//all the rows' sum are equal to each other
		for(int j=0; j<width;j++)
		{
			for(int i=0; i<height;i++)
			{
				sum+=stoi(gameState[i][j]);//every column's sum
			}
			if(sum!=ref)//two columns' sum are equal
				return false;
			sum=0;//reset the sum for calculating the sum of next colomn
		}
		//check out the sum of major diag
		for(int i=0; i<height;i++)
		{
			sum=sum+stoi(gameState[i][i]);
		}
		//the sum of major diag does not match the overall standard
		if(sum!=ref)
			return false;
		else
		{
			sum=0;
			//check out the sum of minor diag
			for(int i=0; i<height;i++)
			{
				sum=sum+stoi(gameState[i][height-i-1]);
			}
			//the sum of minor diag does not match the overall standard
			if(sum!=ref)
				return false;
			else//all rows,colomns and diags are equal
				return true;
		}
	}
	return false;
}

//If done() functions return true, the stalemate() functions return false. Otherwise, stalemate() functions return true.
bool MagicSquareGame::stalemate()
{	
	if(this->boardisFull()){
		if(this->done())
			return false;
		else
			return true;
	}
	else
		return false;
}

//The function defines prompt(), which prompt users to input the coordinates of a gamepiece.
int MagicSquareGame::prompt(unsigned int &fir, unsigned int &sec){
	string inputString;	
	cout << "Please enter a valid coordinate e.g, 0,0 or type quit"<<endl;
	int result;
	while(cin >> inputString){
		if (!strcmp(inputString.c_str(),"quit")){
			throw (int)magicsquare_user_quit;
		}
		else{
			for(unsigned int i =0; i < inputString.length(); i++){
				if(inputString[i] == ','){
					inputString[i] = ' ';
				}
			}
			istringstream iss(inputString);
			if(iss >> fir >> sec){
				if((0<=fir && fir<5) && (0<=sec && sec<5)){
					result = success;	
					break;
				}
			}
		}		
		cout <<"Input is invalid." <<endl;
		cout << "Please enter a valid coordinate e.g, 0,0 or type quit"<<endl;
	}
	return result;
}

//The function prompts users to input a string with the value of an available piece, the method should extract the value into the unsigned integer parameter and return. 
//if users input quit, it will throw an expection.
int MagicSquareGame::prompt(int &inputInt){
	string inputString;	
	int piecenum;
	cout << "Please enter an available gamePiece e.g, 0 or type quit"<<endl;
	if(cin >> inputString){
		if (!strcmp(inputString.c_str(),"quit")){
			throw (int)magicsquare_user_quit;
		}
		else
		{
			istringstream iss(inputString);
			iss>>piecenum;
			if(piecenum >= *(availablePieces.begin()) && piecenum <= *(availablePieces.end()-1)){
				inputInt = piecenum;
			}
			return success;
		}
	}
	else
		return fail;
}

//To judge that if the board is full.
bool MagicSquareGame::boardisFull(){
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j ++){
			if(!strcmp(gameState[i][j].c_str()," ")){
				return false;
			}
		}
	}
	return true;
}

//The function should (repeatedly if necessary) call the overloaded prompt() method to obtain coordinates for an empty square on the board and the value of an available piece to play on that square.
int MagicSquareGame::turn(){
	unsigned int game_des_x, game_des_y;
	int piecenum;
	try
	{
		this->prompt(game_des_y,game_des_x);
	}
	catch(int)
	{ 
		throw (int)magicsquare_user_quit;
	}
	try
	{
		this->prompt(piecenum);
	}
	catch(int)
	{
		throw (int)magicsquare_user_quit;
	}
	if(!strcmp(gameState[game_des_x][game_des_y].c_str()," ")){
		cout << "Coordinate "<<game_des_y <<" " <<game_des_x << endl;
		cout <<"Piecenum " << piecenum <<endl;
		vector<int>::iterator iter = find(availablePieces.begin(), availablePieces.end(),piecenum);
		availablePieces.erase(iter);//erase from the available list
		stringstream ss;
		ss << piecenum;
		string str = ss.str();
		gameState[game_des_x][game_des_y] = str;//put the piece on the game board
		this->print();//print out the current game board
		return success;
	}
	else
		return fail;

}




