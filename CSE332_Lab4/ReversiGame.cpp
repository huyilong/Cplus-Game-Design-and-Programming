//File's name: ReversiGame.cpp 
//Authors: Yang Ye    ye@go.wustl.edu  
//         Yilong Hu  hu.yilong@go.wustl.edu
//		   Chao Zhang zcvictory0329@gmail.com
//Summary: The ReversiGame.cpp defines public members funcions.
#include "stdafx.h"
#include "ReversiGame.h"

const int next_index = 2;
const int startPo = 1;
const int stopPo = 8;
const int boardSize = 8;
const int total_pieces = 64;

//This is a definition of insertion operator. The insertion operator can output the game board.
ostream &operator<<(ostream &out, const ReversiGame &game){
	for (int j = boardSize ; j >= 1; j--){
		out << j-1 <<" ";
		for(int i = 1; i <= boardSize; i++){
			out <<game.gameState[j][i]<<" ";
		}
		out << endl;
	}
	//print out the last row of the gameboard
	out << "X";
	for(int i = 0; i <= boardSize-startPo; i ++)
	{
		out << " " << i;
	}
	out << endl;
	return out;
}

//This is the ReversiGame constructor. This constructor can judge that if We will play the game from the beginning or continue the game from the step we did last time.
ReversiGame::ReversiGame(string black_player, string white_player,ifstream &gameFile){
	GameName = "Reversi";
	if(gameFile.good()){
		string fLine;
		getline(gameFile,fLine);
		//If the file shows No Data int the first line, it means the player will play the game from the beginning.
		if(fLine == "NO DATA"){
			(*this).black_player = black_player;
			(*this).white_player = white_player;
			width = boardSize;
			height = boardSize; 
			vector<string> row;
			for(int i = 0; i < height+next_index; i ++){
				for(int j = 0; j < width+next_index; j ++){
					row.push_back(" ");
				}
				gameState.push_back(row);
			}

			//initialize the gameboard if there is no input stream
			gameState[4][4] = "X";
			gameState[5][5] = "X";
			gameState[4][5] = "O";
			gameState[5][4] = "O";
			//initialize the current_player with black_player
			(*this).current_player = black_player;	
		}
		//Otherwise the player can choose whether he will continue the game from the step he did past or not.
		else if(fLine == "GAME SAVED"){
			cout << "Do you want to continue the unfinished game?(YyNn)"<<endl;
			char load_flag;
			cin >> load_flag;
			while(load_flag != 'y' && load_flag !='n' && load_flag != 'Y' && load_flag != 'N'){
				cout << "Please enter Y or y or N or n " << endl;
				cin >> load_flag;
			}
			//If the player chooses y, he will continue the game.
			if(load_flag == 'y'){
				getline(gameFile,fLine);
				istringstream iss(fLine);
				if(!(iss >> (*this).current_player >> (*this).black_player >> (*this).white_player)){
					cout << "Can't read player's names"<<endl;
				}
				width = boardSize;
				height = boardSize;
				vector<string> row;
				for(int i = 0; i < height+next_index; i ++){
					for(int j = 0; j < width+next_index; j ++){
						row.push_back(" ");
					}
					gameState.push_back(row);
				}
				while(getline(gameFile,fLine)){
					string gamePiece;
					int i,j;
					istringstream iss2(fLine);
					if(!(iss2 >> gamePiece >> i >> j))
					{
						cout<<"can't load game"<<endl;
						break;
					}
					gameState[i][j] = gamePiece;
				}
			}
			//Ohterwise he will play the game from the beginning.
			else{
				(*this).black_player = black_player;
				(*this).white_player = white_player;
				width = boardSize;
				height = boardSize; 
				vector<string> row;
				for(int i = 0; i < height+next_index; i ++){
					for(int j = 0; j < width+next_index; j ++){
						row.push_back(" ");
					}
					gameState.push_back(row);
				}
				//initialize the gameboard if there is no input stream
				gameState[4][4] = "X";
				gameState[5][5] = "X";
				gameState[4][5] = "O";
				gameState[5][4] = "O";
				//initialize the current_player with black_player
				(*this).current_player = black_player;	
			}
		}
	}
}

void ReversiGame::print(){
	cout << (*this) << endl;
}

//The done() method return true if either (1) all pieces on the board are of the same color or
//(2) there are more pieces of one color than another color on the board and either of the following is true: 
//(a) all squares are filled; or (b) there are no remaining legal moves for either player. otherwise the method should return false.
bool ReversiGame::done(){
	bool result = false;
	int black_num,white_num,blank_num;
	black_num = white_num = blank_num = 0;
	//calculate the number of the total white checkers, black checkers and blank places on the board
	for(int i = 1; i <= width; i ++){
		for(int j = 1; j <= height; j ++){
			if(gameState[i][j]=="X")
				black_num++;
			else if(gameState[i][j]=="O")
				white_num++;
			else
				blank_num++;
		}
	}
	//all pieces on the board are of the same color
	if(black_num == total_pieces || white_num == total_pieces){
		if(black_num == total_pieces)
		{
			cout<<"Congratulations! The winner is "<<black_player<<" !"<<endl;
			cout <<black_player<<" has " <<"64 pieces"<<endl;
			cout <<white_player<<" has " <<"0 pieces"<<endl;
		}
		else
		{
			cout<<"Congratulations! The winner is "<<white_player<<" !"<<endl;
			cout <<black_player<<" has " <<"0 pieces"<<endl;
			cout <<white_player<<" has " <<"64 pieces"<<endl;
		}
		result = true;
	}
	//there are more pieces of one color than another color on the board
	//and there are no remaining legal moves for either player
	else if((black_num != white_num) && !hasValidSquare() ){
		if(black_num>white_num)
		{
			cout<<"Congratulations! The winner is "<<black_player<<" !"<<endl;
			cout <<black_player<<" has " << black_num <<" pieces"<<endl;
			cout <<white_player<<" has " << white_num <<" pieces"<<endl;
		}
		else
		{
			cout<<"Congratulations! The winner is "<<white_player<<" !"<<endl;
			cout <<black_player<<" has " << black_num <<" pieces"<<endl;
			cout <<white_player<<" has " << white_num <<" pieces"<<endl;
		}
		result = true;
	}
	return result;
}

//The stalemate() method return true if both (1) there are the same number of black pieces and white pieces on the board and
//(2) either of the following is true: (a) all squares are filled; or (b) there are no remaining legal moves for either player; 
//otherwise the method return false.
bool ReversiGame::stalemate(){
	bool result = false;
	int black_num,white_num,blank_num;
	black_num = white_num = blank_num = 0;
	//calculate the number of the total white checkers, black checkers and blank places on the board
	for(int i = 1; i <= height; i ++){
		for(int j = 1; j <= width; j ++){
			if(gameState[i][j]=="X")
				black_num++;
			else if(gameState[i][j]=="O")
				white_num++;
			else
				blank_num++;
		}
	}
	//there are the same number of black pieces and white pieces on the board
	//and there are no remaining legal moves for either player
	if((black_num == white_num) && !hasValidSquare() ){
		cout<<"Ooops! You meet with a stalemate!"<<endl;
		result = true;
	}
	return result;
}

//The hasValidSquare() method return true if it finds valid square else return false.
bool ReversiGame::hasValidSquare()
{
	bool result = false;
	result = (checkValid("X","O")||checkValid("O","X"));
	return result;
}

//The checkValid() method gives the specific standard to judge that from 8 different directions whether the square is valid or not.
bool ReversiGame::checkValid(string current, string opposite){
	for(int i = 1;i <= height;i++){
		for(int j=1;j <= width;j++){
			if(gameState[i][j] == " "){
				if(gameState[i-1][j] == opposite){
					for (int kk = next_index; i-kk >= startPo; kk++){
						if(gameState[i-kk][j] == current){
							return true;
						}
						else if(gameState[i-kk][j] == " "){
							break;
						}
					}
				}
				if (gameState[i-1][j-1] == opposite){
					for(int kk = next_index;(i-kk >= startPo)&&(j-kk >= startPo);kk++){
						if(gameState[i-kk][j-kk] == current){
							return true;
						}
						else if(gameState[i-kk][j-kk] == " "){
							break;
						}
					}
				}
				if (gameState[i-1][j+1] == opposite){
					for(int kk = next_index;(i-kk>=startPo)&&(j+kk<=stopPo);kk++){
						if(gameState[i-kk][j+kk] == current){
							return true;
						}
						else if(gameState[i-kk][j+kk] == " "){
							break;
						}
					}
				}
				if (gameState[i][j-1] == opposite){
					for(int kk = next_index; j-kk>=startPo ;kk++){
						if(gameState[i][j-kk] == current){
							return true;
						}
						else if(gameState[i][j-kk] == " "){
							break;
						}
					}
				}
				if (gameState[i][j+1] == opposite){
					for(int kk = next_index;j+kk<=stopPo;kk++){
						if(gameState[i][j+kk] == current){
							return true;
						}
						else if(gameState[i][j+kk] == " "){
							break;

						}
					}
				}
				if (gameState[i+1][j-1] == opposite){
					for(int kk = next_index;(i+kk<=stopPo)&&(j-kk>=startPo);kk++){
						if(gameState[i+kk][j-kk] == current){
							return true;
						}
						else if(gameState[i+kk][j-kk] == " "){
							break;
						}
					}
				}
				if (gameState[i+1][j+1] == opposite){
					for(int kk = next_index;(i+kk<=stopPo)&&(j+kk<=stopPo);kk++){
						if(gameState[i+kk][j+kk] == current){
							return true;
						}
						else if(gameState[i+kk][j+kk] == " "){
							break;
						}
					}
				}
				if (gameState[i+1][j] == opposite){
					for(int kk = next_index;i+kk<=stopPo;kk++){
						if(gameState[i+kk][j] == current){
							return true;
						}
						else if(gameState[i+kk][j] == " "){
							break;
						}
					}
				}
			}
		}
	}
	return false;
}

//The moveisValid() method to put black or white piece on the valid square. 
bool ReversiGame::moveisValid(string current,string opposite,unsigned int player_x,unsigned int player_y){
	bool result = false;
	if((player_x <= stopPo) && (player_y <= stopPo) && (player_y >= startPo) &&(player_x >= startPo)){
		int i = player_x, j = player_y;
		if(gameState[i][j] == " "){
			if(gameState[i-1][j] == opposite){
				for (int kk = 2; i-kk >= startPo; kk++){
					if(gameState[i-kk][j] == current){
						for (int flip = i-kk; flip<=i; flip++)
						{
							gameState[flip][j] = current;
						}
						result = true;
					}
					else if(gameState[i-kk][j] == " "){
						break;
					}
				}

			}
			if (gameState[i-1][j-1] == opposite){
				for(int kk = 2;(i-kk >= startPo)&&(j-kk >= startPo);kk++){
					if(gameState[i-kk][j-kk] == current){
						for(int flip1=i-kk,flip2=j-kk; flip1<=i && flip2<=j; flip1++,flip2++){
							gameState[flip1][flip2] = current;
						}
						result = true;
					}
					else if(gameState[i-kk][j-kk] == " "){
						break;
					}
				}
			}
			if (gameState[i-1][j+1] == opposite){
				for(int kk = 2;(i-kk>=startPo)&&(j+kk<=stopPo);kk++){
					if(gameState[i-kk][j+kk] == current){
						for(int flip1=i-kk, flip2=j+kk; flip1<=i && flip2>=j; flip1++,flip2--){
							gameState[flip1][flip2] = current;
						}
						result = true;
					}
					else if(gameState[i-kk][j+kk] == " "){
						break;
					}
				}

			}
			if (gameState[i][j-1] == opposite){
				for(int kk = 2; j-kk>=startPo ;kk++){
					if(gameState[i][j-kk] == current){
						for(int flip=j-kk; flip<=j; flip++){
							gameState[i][flip] = current;
						}
						result = true;
					}
					else if(gameState[i][j-kk] == " "){
						break;
					}
				}
			}
			if (gameState[i][j+1] == opposite){
				for(int kk = 2;j+kk<=stopPo;kk++){
					if(gameState[i][j+kk] == current){
						for(int flip=j+kk; flip>=j; flip--){
							gameState[i][flip] = current;
						}
						result = true;
					}
					else if(gameState[i][j+kk] == " "){
						break;
					}
				}
			}
			if (gameState[i+1][j-1] == opposite){
				for(int kk = 2;(i+kk<=stopPo)&&(j-kk>=startPo);kk++){
					if(gameState[i+kk][j-kk] == current){
						for(int flip1=i+kk,flip2=j-kk; flip1>=i && flip2<=j; flip1--,flip2++){
							gameState[flip1][flip2] = current;
						}
						result = true;
					}
					else if(gameState[i+kk][j-kk] == " "){
						break;
					}
				}
			}
			if (gameState[i+1][j+1] == opposite){
				for(int kk = 2;(i+kk<=stopPo)&&(j+kk<=stopPo);kk++){
					if(gameState[i+kk][j+kk] == current){
						for(int flip1=i+kk,flip2=j+kk; flip1>=i && flip2>=j; flip1--,flip2--){
							gameState[flip1][flip2] = current;
						}
						result = true;
					}
					else if(gameState[i+kk][j+kk] == " "){
						break;
					}
				}
			}
			if (gameState[i+1][j] == opposite){
				for(int kk = 2;i+kk<=stopPo;kk++){
					if(gameState[i+kk][j] == current){
						for(int flip=i+kk; flip>=i; flip--){
							gameState[flip][j] = current;
						}
						result = true;
					}
					else if(gameState[i+kk][j] == " "){
						break;
					}
				}
			}
		}
	}
	return result;
}

//The turn() method remember which player's turn it is, the method print out a message to that effect and
//the method alternate whose turn it is each time it is called.
int ReversiGame::turn(){
	cout<<"This is the turn for " << current_player<<endl;
	if(current_player == black_player)
	{
		string current = "X";
		string opposite = "O";
		//if the black_player has valid square to place 'X'
		if(!checkValid(current,opposite))
		{
			cout<<"Sorry, "<<current_player <<" You do not have a remaining valid move."<<endl;
			//using checker 'X' next time calling turn()
			current_player = white_player;
			return one_player_done;
		}
	}
	else if(current_player == white_player)
	{
		string current = "O";
		string opposite = "X";
		if(!checkValid(current,opposite))
		{
			cout<<"Sorry, "<<current_player <<" You do not have a remaining valid move."<<endl;
			//using checker 'X' next time calling turn()
			current_player = black_player;
			return one_player_done;
		}
	}
	unsigned int user_des_x, user_des_y;
	int prompt_flag = this->prompt(user_des_x,user_des_y);
	if (prompt_flag == reversi_user_quit){
		return reversi_user_quit;
	}
	else if((prompt_flag == success)){
		unsigned int game_des_x = user_des_y;
		unsigned int game_des_y = user_des_x;
		if(current_player == black_player)
		{
			string current = "X";
			string opposite = "O";
			//if the black_player has valid square to place 'X'
			if(moveisValid(current,opposite,game_des_x,game_des_y))
			{
				//using checker 'X' next time calling turn()
				current_player = white_player;
				cout <<(*this) <<endl;
				return one_turn_done;
			}
			else//the move is not valid
			{
				cout << endl;
				cout << "Your move is invalid, Please try an another move\n" << endl;
			}
		}
		else
		{
			string current = "O";
			string opposite = "X";
			if(moveisValid(current,opposite,game_des_x,game_des_y))
			{
				//using checker 'X' next time calling turn()
				current_player = black_player;
				cout <<(*this) <<endl;
				return one_turn_done;
			}
			else//the move is not valid
			{
				cout << endl;
				cout << "Your move is invalid, Please try an another move\n" << endl;
			}
		}
	}
	return success;
}

//The prompt() method prompt players to input coordinate or quit.
int ReversiGame::prompt(unsigned int &fir, unsigned int &sec){
	string inputString;
	cout << "Please enter a valid coordinate e.g, 0,0 or type quit"<<endl;
	int result;
	while(cin >> inputString){
		if (inputString == "quit"){
			cout <<"Do you want to save the current game?(YyNn)"<<endl;
			char save_flag;
			cin >> save_flag;
			while(save_flag != 'y' && save_flag !='n' && save_flag != 'Y' && save_flag != 'N'){
				cout << "Please enter Y or y or N or n " << endl;
				cin >> save_flag;
			}
			ofstream gameFile;
			gameFile.open("Reversi.txt");
			if(save_flag == 'y' || save_flag == 'Y'){
				gameFile << "GAME SAVED\n";
				gameFile << current_player <<" " << black_player<< " " <<white_player<< endl;
				for(int i = width;i>=1;i--){
					for(int j = 1;j <= height;j++){
						if(gameState[i][j] != " "){
							gameFile<< gameState[i][j] <<" "<< i <<" "<< j << endl;;
						}
					}
				}
				cout << "Game Saved!" <<endl;
				gameFile.close();
			}
			if(save_flag == 'n' || save_flag == 'N'){
				gameFile << "NO DATA";
				gameFile.close();
			}

			result = reversi_user_quit;
			break;
		}
		else{
			for(unsigned int i =0; i < inputString.length(); i++){
				if(inputString[i] == ','){
					inputString[i] = ' ';
				}
			}
			istringstream iss(inputString);
			if(iss >> fir >> sec){
				if(((startPo-1)<=fir && fir<stopPo) && ((startPo-1)<=sec && sec<=stopPo)){
					fir++;
					sec++;
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

//this prompt does nothing but override the virtual function in base class so that it could be instantialized
int ReversiGame::prompt(int &inputInt){
	return 0;
}