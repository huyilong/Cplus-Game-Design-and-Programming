//File's name: NineAlmondsGame.cpp
//Authors: Yang Ye    ye@go.wustl.edu  
//         Yilong Hu  hu.yilong@go.wustl.edu  
//	       Chao Zhang zcvictory0329@gmail.com
//Summary: The NineAlmondsGame.cpp defines the public member functions.

#include "stdafx.h"
#include "NineAlmondsGame.h"

//JZ: this is rather hard-coded, no?
//in fact, a lot of the code in here is. On the one hand you could've avoided
//this by using enums, #defining, etc., but on the other hand it's true that
//the game is called NineAlmonds and not 'n' almonds, so let's let that slide
// 
//This is the initial gameboard.
const string init_row4 [5] ={" "," "," "," "," "};
const string init_row3 [5] ={" ","A","A","A"," "};
const string init_row2 [5] ={" ","A","A","A"," "};
const string init_row1 [5] ={" ","A","A","A"," "};
const string init_row0 [5] ={" "," "," "," "," "};

//Enum for all possible return values
enum return_value{success, fail, wrongGameName, too_many_input, not_enough_input, unable_to_read_coordinate, invalidMove,stalemateOccured, ninealmonds_user_quit, magicsquare_user_quit, bad_Alloc, unknown_exception, other_exception};

//JZ: REALLY should've put that enum into a separate header file (say 'CSE332_Lab3.h' along w/ other methods in CSE332_Lab3.cpp)...

//This is the << operation for printing out the game state. Since my initial game board doesn't 
//have the coordinate number like x 0 1 2 3 4, So i will add it to the game board every time I print the gameboard.
ostream &operator<<(ostream &out, const NineAlmondsGame &game){
	for (int j = game.height-1; j >= 0; j--){
		out << j <<" ";
		for(int i = 0; i < game.width; i++){
			if(i == 0){
			out << game.gameState[j][i];
			}
			else{
			out << setw(game.longestPieceLength - game.gameState[j][i].length()+2) << game.gameState[j][i];
			}
		}
		out << endl;
	}

	out << "X";
	for(int i = 0; i < game.width; i ++)
		out << setw(game.longestPieceLength+1) << i;
	out << endl;
	return out;
}

//This is the NineAlmondsGame object default constructor. Everytime i create a NineAlmondsGame, the game board
//is initialized. There is a 2d vecter in the game object to store the gameboard, i just simple push all the elements into
//the 2d vector when I construct an object.
NineAlmondsGame::NineAlmondsGame(){
	height = 5;
	width = 5;
	longestPieceLength = 0;
	
	for(int i = 0; i < height; i++){
		vector<string> row;
		switch (i){
		case 0:
			for(int j = 0; j < width; j++){
				if (init_row0[j].length() > longestPieceLength){
					longestPieceLength = init_row0[j].length();
				}
				row.push_back(init_row0[j]);
			}
			break;
		case 1:
			for(int j = 0; j < width; j++){
				if (init_row1[j].length() > longestPieceLength){
					longestPieceLength = init_row1[j].length();
				}
				row.push_back(init_row1[j]);
			}
			break;
		case 2:
			for(int j = 0; j < width; j++){
				if (init_row2[j].length() > longestPieceLength){
					longestPieceLength = init_row2[j].length();
				}
				row.push_back(init_row2[j]);
			}
			break;
		case 3: 
			for(int j = 0; j < width; j++){
				if (init_row3[j].length() > longestPieceLength){
					longestPieceLength = init_row3[j].length();
				}
				row.push_back(init_row3[j]);
			}
			break;
		case 4:
			for(int j = 0; j < width; j++){
				if (init_row4[j].length() > longestPieceLength){
					longestPieceLength = init_row4[j].length();
				}
				row.push_back(init_row4[j]);
			}
			break;
		}
		gameState.push_back(row);
	}

}

void NineAlmondsGame::print(){
	cout << (*this) << endl;
}

//This is the function to test whether the game is win or not. I simply test if there is an almond in position[2][2],
//and all the other positions don't have almonds.
bool NineAlmondsGame::done(){
	bool result = false;
	if (gameState[2][2] == "A"){
		result = true;
		for(int i=0; i < height; i++){
			for(int j=0; j < width; j++){
				if(gameState[i][j] != " " && i != 2 && j != 2){
					result = false;
				}
			}
		}
	}
	return result;
}

//This is the function to test whether the current gamestate is a stalemate or not.
//I check the inner 16 position(which are those have coordinate x<5,y<5), and check if their
//up or right or up-right block has an almond or not. If one those positions have almonds, then
//current game state is not a stalemate.
bool NineAlmondsGame::stalemate(){
	if (this->done()){
		return false;
	}
	else{
		bool result = true;

		for(int i=0; i < height-1; i++){
			for(int j=0; j < width-1; j++){
				int neighborCount = 0;
				for(int kk = 0; kk < 2; kk++){
					for (int hh = 0; hh < 2; hh++){
						if(gameState[i+hh][j+kk] == "A"){	
							neighborCount++;
						}
					}
				}
				if(neighborCount > 1){
					result = false;
				}
			}
		}
		return result;
	}
}

//This is the prompt funtion to read the corrdinate that given by the user.
//Since the gameboard has size 5X5, so we can't have any input x and y larger than 5 or have negative value.
// So I test whether a input is valid, then stringsteam then two unsigned integers.
int NineAlmondsGame::prompt(unsigned int &fir, unsigned int &sec){
	string inputString;	
	cout << "Please enter a valid coordinate e.g, 0,0 or type quit"<<endl;
	int result;
	while(cin >> inputString){
		if (inputString == "quit"){
			result = ninealmonds_user_quit;
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

//This prompt funtion is not used in the NineAlmonds class. However, it is a pure vitual method in its parent class, so we need to define it here, but it does nothing.
int NineAlmondsGame::prompt(int &inputInt){
	return 0;
}

//This function checks whethere a move is valid or not. This function takes four unsigned integer as inputs and two refernece unsigned integer .
//The first, and second are the x and y coordinate for the almond that user wants move. The third and fourth are the desitnation that user wants to place the alomond.
//The last two inputs are use to save the x and y coordinates of the almond that is between the start almond and desitnation.
//First we check that the staring position is not equal to the destination position. Then I check is there a almond on the starting position. 
//Next I check if the destination position is 2 block away from the starting position(vertical, horizontal, diagonal). Last, I check is there a almond that is between starting almond and destination point.
bool NineAlmondsGame::moveisValid(unsigned int player_almond_x,unsigned int player_almond_y,unsigned int player_destination_x,unsigned int player_destination_y,unsigned int &almondBetween_x, unsigned int &almondBetween_y){
	int game_almond_x = player_almond_x;
	int game_almond_y = player_almond_y;
	int game_destination_x = player_destination_x;
	int game_destination_y = player_destination_y;
	if(game_almond_x != game_destination_x || game_almond_y != game_destination_y){
		if((*this).gameState[game_almond_x][game_almond_y] == "A"){
			if(((game_destination_x == game_almond_x) || (game_destination_x == game_almond_x+2) || (game_destination_x == game_almond_x-2)) && ((game_destination_y == game_almond_y) || (game_destination_y == game_almond_y+2) || (game_destination_y == game_almond_y-2))){
				if((*this).gameState[game_destination_x][game_destination_y] == " "){	
					almondBetween_x = (game_destination_x - game_almond_x)/2 + game_almond_x;
					almondBetween_y = (game_destination_y - game_almond_y)/2 + game_almond_y;
					if((*this).gameState[almondBetween_x][almondBetween_y] == "A"){
						return true;
					}
				}
			}
		}
	}
	return false;
}

//This function calls promt funtion two time to get the staring almond position and the destination position.
//It will check whether a move is valid or, if it is valid, it will remove the almond on the starting position,
//also remove the almond that is between starting position and the detination position. Last, it places an almond
//on the destination position. After all of that, it will ask the user to continue this turn or not. If the user type
//y(yes). Then I assign the coordinate of desitnation to be the current almond's corrdinate, and ask user for a new destination
//coordinate. Then do the above valid check again. I will do this and this again until the user hits n(no) to not continue this turn.
int NineAlmondsGame::turn(){
	unsigned int user_almond_x, user_almond_y;
	unsigned int user_des_x, user_des_y;

	if((this->prompt(user_almond_x,user_almond_y) == success)){
		if((this->prompt(user_des_x,user_des_y) == success)){
			unsigned int game_almond_x = user_almond_y;
			unsigned int game_almond_y = user_almond_x;
			unsigned int game_des_x = user_des_y;
			unsigned int game_des_y = user_des_x;
			unsigned int middleAlmond_x, middleAlmond_y;

			if(this->moveisValid(game_almond_x,game_almond_y,game_des_x,game_des_y, middleAlmond_x,middleAlmond_y)){
				(*this).gameState[middleAlmond_x][middleAlmond_y] = ' ';
				(*this).gameState[game_almond_x][game_almond_y] = ' ';
				(*this).gameState[game_des_x][game_des_y] = 'A';
				cout << (*this) << "\n" <<endl;
				ostringstream moveRecord;
				moveRecord << user_almond_x << ',' << user_almond_y << " to " << user_des_x << ',' << user_des_y;
				cout << moveRecord.str()<< "\n" << endl;
				cout << "Continue this turn(YyNn)?"<<endl;
				char continue_flag;
				cin >> continue_flag;
				while(continue_flag != 'y' && continue_flag !='n'){
					cout << "Please type y or n " << endl;
					cin >> continue_flag;
				}
				while(continue_flag == 'y'){
					game_almond_x = game_des_x;
					game_almond_y = game_des_y;
					if(this->prompt(game_des_y,game_des_x) == success){
						if(this->moveisValid(game_almond_x,game_almond_y,game_des_x,game_des_y,middleAlmond_x,middleAlmond_y)){
							(*this).gameState[middleAlmond_x][middleAlmond_y] = ' ';
							(*this).gameState[game_almond_x][game_almond_y] = ' ';
							(*this).gameState[game_des_x][game_des_y] = 'A';
							cout << (*this) << "\n" <<endl;
							moveRecord << " to " << game_des_y << ',' << game_des_x;
							cout << moveRecord.str() <<"\n"<<endl;
							cout << "Continue this turn(YyNn)?"<<endl;
							cin >> continue_flag;
							while(continue_flag != 'y' && continue_flag !='n'){
								cout << "Please typr y or n " << endl;
								cin >> continue_flag;
							}
						}
						else{
							cout << "You move is invalid, Continue this turn(YyNn)?" << endl;
							cin >> continue_flag;
							while(continue_flag != 'y' && continue_flag !='n'){
								cout << "Please typr y or n " << endl;
								cin >> continue_flag;
							}
						}
					}
					else{
						return ninealmonds_user_quit;
					}
				}
				return success;
			}
			return invalidMove;
		}
	}
	return ninealmonds_user_quit;
}



























