

#include "stdafx.h"
/*
#include "EnglishDraughts.h"

const int next_index = 2;
const int boardSize = 8;

ostream &operator<<(ostream &out, const ReversiGame &game){
	for (int j = boardSize; j >= 1; j--){
		out << j - 1 << " ";
		for (int i = 1; i <= boardSize; i++){
			out << game.gameState[j][i] << " ";
		}
		out << endl;
	}
	//print out the last row of the gameboard
	out << "X";
	for (int i = 0; i <= boardSize - startPo; i++)
	{
		out << " " << i;
	}
	out << endl;
	return out;
}

EnglishDraughts::EnglishDraughts(string black_player, string white_player){
	(*this).black_player = black_player;
	(*this).white_player = white_player;
	width = boardSize;
	height = boardSize;
	vector<string> row;
	for (int i = 0; i < height+next_index; i++){
		for (int j = 0; j < width+next_index; j++){
			row.push_back(" ");
		}
		gameState.push_back(row);
	}

	//initialize the gameboard if there is no input stream
	for (int i = boardSize; i >= boardSize-next_index; i--)
	{
		if (i % next_index == 0)
		{
			for (int j = next_index; j<= boardSize; j += next_index)
			{
				gameState[i][j] = "X";
			}
		}
		else
			for (int j = 1; j<= boardSize; j += next_index)
			{
				gameState[i][j] = "X";
			}
	}

	for (int i = next_index+1; i >= 0; i--)
	{
		if (i % next_index != 0)
		{
			for (int j = 1; j<= boardSize; j += next_index)
			{
				gameState[i][j] = "O";
			}
		}
		else
			for (int j = next_index; j<= boardSize; j += next_index)
			{
				gameState[i][j] = "O";
			}
	}

	//initialize the current_player with black_player
	current_player = black_player;
}

void EnglishDraughts::print(){
	cout << (*this) << endl;
}



bool EnglishDraughts::done(){
	bool result = false;
	int black_num, white_num, blank_num;
	black_num = white_num = blank_num = 0;
	//calculate the number of the total white checkers, black checkers and blank places on the board
	for (int i = 1; i <= height; i++){
		for (int j = 1; j <= width; j++){
			if (gameState[i][j] == "X")
				black_num++;
			else if (gameState[i][j] == "O")
				white_num++;
		}
	}
	//all pieces on the board are of the same color
	if ((black_num > 0 && white_num == 0) || (white_num > 0 && black_num == 0)){
		result = true;
	}
	//there are more pieces of one color than another color on the board
	//and there are no remaining legal moves for either player
	else if ((black_num != white_num) && !hasValidSquare()){
		result = true;
	}
	return result;
}



bool EnglishDraughts::stalemate(){
	bool result = false;
	int black_num,white_num;
	black_num = white_num = 0;
	//calculate the number of the total white checkers, black checkers and blank places on the board
	for(int i = 1; i <= height; i ++){
		for(int j = 1; j <= width; j ++){
			if(gameState[i][j]=="X")
				black_num++;
			else if(gameState[i][j]=="O")
				white_num++;
		}
	}
	//there are the same number of black pieces and white pieces on the board
	//and there are no remaining legal moves for either player
	if((black_num == white_num) && !hasValidSquare() ){
		result = true;
	}
	return result;
}

bool EnglishDraughts::hasValidSquare()
{
	bool result = false;
	if(current_player == black_player)
	{
		string current = "X";
		string opposite = "O";
		result = checkValid(current,opposite);
	}
	else if (current_player == white_player)
	{
		string current = "O";
		string opposite = "X";
		result = checkValid(current,opposite);
	}
	return result;
}

bool EnglishDraughts::checkValid(string current, string opposite){
	for(int i = 0 ;i <= height-1;i++){
		for(int j = 0;j <= width-1;j++){
			if(gameState[i][j] == " "){
				if(gameState[i-1][j] == opposite){
					for (int kk = 2; i-kk >= 0; kk++){
						if(gameState[i-kk][j] == current){
							return true;
						}
						else if(gameState[i-kk][j] == " "){
							break;
						}
					}
				}
				if (gameState[i-1][j-1] == opposite){
					for(int kk = 2;(i-kk >= 0)&&(j-kk >= 0);kk++){
						if(gameState[i-kk][j-kk] == current){
							return true;
						}
						else if(gameState[i-kk][j-kk] == " "){
							break;
						}
					}
				}
				if (gameState[i-1][j+1] == opposite){
					for(int kk = 2;(i-kk>=0)&&(j+kk<8);kk++){
						if(gameState[i-kk][j+kk] == current){
							return true;
						}
						else if(gameState[i-kk][j+kk] == " "){
							break;
						}
					}

				}
				if (gameState[i][j-1] == opposite){
					for(int kk = 2; j-kk>=0 ;kk++){
						if(gameState[i][j-kk] == current){
							return true;
						}
						else if(gameState[i][j-kk] == " "){
							break;
						}
					}
				}
				if (gameState[i][j+1] == opposite){
					for(int kk = 2;j+kk<8;kk++){
						if(gameState[i][j+kk] == current){
							return true;
						}
						else if(gameState[i][j+kk] == " "){
							break;
						}
					}
				}
				if (gameState[i+1][j-1] == opposite){
					for(int kk = 2;(i+kk<8)&&(j-kk>=0);kk++){
						if(gameState[i+kk][j-kk] == current){
							return true;
						}
						else if(gameState[i+kk][j-kk] == " "){
							break;
						}
					}
				}
				if (gameState[i+1][j+1] == opposite){
					for(int kk = 2;(i+kk<8)&&(j+kk<8);kk++){
						if(gameState[i+kk][j+kk] == current){
							return true;
						}
						else if(gameState[i+kk][j+kk] == " "){
							break;
						}
					}
				}
				if (gameState[i+1][j] == opposite){
					for(int kk = 2;i+kk<8;kk++){
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

bool ReversiGame::moveisValid(string current,string opposite,unsigned int player_x,unsigned int player_y){
	bool result = false;
	if((player_x <= 8) && (player_y <= 8) && (player_y >= 1) &&(player_x >= 1)){
		int i = player_x, j = player_y;
		if(gameState[i][j] == " "){
			if(gameState[i-1][j] == opposite){
				for (int kk = 2; i-kk >= 0; kk++){
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
				for(int kk = 2;(i-kk >= 0)&&(j-kk >= 0);kk++){
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
				for(int kk = 2;(i-kk>=0)&&(j+kk<8);kk++){
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
				for(int kk = 2; j-kk>=0 ;kk++){
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
				for(int kk = 2;j+kk<8;kk++){
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
				for(int kk = 2;(i+kk<8)&&(j-kk>=0);kk++){
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
				for(int kk = 2;(i+kk<8)&&(j+kk<8);kk++){
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
				for(int kk = 2;i+kk<8;kk++){
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

int ReversiGame::turn(){
	cout << "This is the turn for " << current_player << endl;
	if (current_player == black_player)
	{
		string current = "X";
		string opposite = "O";
		//if the black_player has valid square to place 'X'
		if (!checkValid(current, opposite))
		{
			cout << "Sorry, " << current_player << " You do not have a remaining valid move." << endl;
			//using checker 'X' next time calling turn()
			current_player = white_player;
			return one_player_done;
		}
	}
	else if (current_player == white_player)
	{
		string current = "O";
		string opposite = "X";
		if (!checkValid(current, opposite))
		{
			cout << "Sorry, " << current_player << " You do not have a remaining valid move." << endl;
			//using checker 'X' next time calling turn()
			current_player = black_player;
			return one_player_done;
		}
	}
	unsigned int user_des_x, user_des_y;
	int prompt_flag = this->prompt(user_des_x, user_des_y);
	if (prompt_flag == reversi_user_quit){
		return reversi_user_quit;
	}
	else if ((prompt_flag == success)){
		unsigned int game_des_x = user_des_y;
		unsigned int game_des_y = user_des_x;
		if (current_player == black_player)
		{
			string current = "X";
			string opposite = "O";
			//if the black_player has valid square to place 'X'
			if (moveisValid(current, opposite, game_des_x, game_des_y))
			{
				//using checker 'X' next time calling turn()
				current_player = white_player;
				cout << (*this) << endl;
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
			if (moveisValid(current, opposite, game_des_x, game_des_y))
			{
				//using checker 'X' next time calling turn()
				current_player = black_player;
				cout << (*this) << endl;
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

int ReversiGame::prompt(unsigned int &fir, unsigned int &sec){
	string inputString;
	cout << "Please enter a valid coordinate e.g, 0,0 or type quit" << endl;
	int result;
	while (cin >> inputString){
		if (inputString == "quit"){
			cout << "Do you want to save the current game?(YyNy)" << endl;
			char save_flag;
			cin >> save_flag;
			while (save_flag != 'y' && save_flag != 'n'){
				cout << "Please enter y or n " << endl;
				cin >> save_flag;
			}
			ofstream gameFile;
			gameFile.open("Reversi.txt");
			if (save_flag == 'y'){
				gameFile << "GAME SAVED\n";
				gameFile << current_player << " " << black_player << " " << white_player << endl;
				for (int i = width; i >= 1; i--){
					for (int j = 1; j <= height; j++){
						if (gameState[i][j] != " "){
							gameFile << gameState[i][j] << " " << i << " " << j << endl;;
						}
					}
				}
				cout << "Game Saved!" << endl;
				gameFile.close();
			}
			if (save_flag == 'n'){
				gameFile << "NO DATA";
				gameFile.close();
			}

			result = reversi_user_quit;
			break;
		}
		else{
			for (unsigned int i = 0; i < inputString.length(); i++){
				if (inputString[i] == ','){
					inputString[i] = ' ';
				}
			}
			istringstream iss(inputString);
			if (iss >> fir >> sec){
				if (((startPo - 1) <= fir && fir < stopPo) && ((startPo - 1) <= sec && sec <= stopPo)){
					fir++;
					sec++;
					result = success;
					break;
				}
			}
		}
		cout << "Input is invalid." << endl;
		cout << "Please enter a valid coordinate e.g, 0,0 or type quit" << endl;
	}
	return result;
}

//this prompt does nothing but override the virtual function in base class so that it could be instantialized
int ReversiGame::prompt(int &inputInt){
	return 0;
}
*/