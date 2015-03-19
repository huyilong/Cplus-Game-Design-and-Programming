
/*
File name:gamefunctions.cpp

Author:Hu Yilong

E-mail Address: hu.yilong@wustl.edu

Summary: This file includes the definitions of message to inform user
of correct usage of this program and the stringToEnum function written
in the previous lab and used in this one, and the core definitions of 
functions and variables used in the nine almonds game, which include
done(), turn(), stalemate(), prompt(), continue_prompt(), and play().
There is also a definition of operator so that it can conveniently
print out the contents of game board for the program.
*/

#include "stdafx.h"
#include "lab2header.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <istream>
#include <fstream>
using namespace std;

//when the number of commands typed in by user is wrong, print out the message and return fail
int message(string name, string hint)
{
	cout<<"program name: "<<name<<" usage:"<<hint<<endl;
	return usagefailure;//return a value indicating the failure of command from user
}


// read by string and return a piece_color value
int stringToEnum(string str)
{
	if(str==" ")//conver empty string into enumeration label "nocolor"
	{
		return nocolor;
	}
	else if(str=="red")//conver string "red" into enumeration label "red"
	{
		return red;
	}
	else if(str=="black")//conver string "black" into enumeration label "black"
	{
		return black;
	}
	else if(str=="white")//conver string "white" into enumeration label "white"
	{
		return white;
	}
	else if(str=="brown")//the color used in nine almonds game
	{
		return brown;
	}
	else //not a valid string
	{
		return invalidcolor;
	}

}
//define the operator which can print out the current state of the game board
ostream & operator<<(ostream &out, const single_player &player)
{
	int flag=0;
	for(int y = (player.height-1); y >= 0; --y)//start printing out from the upper side of the whole game board
	{
		out<<y<<" "; //print out the y-axis
		for(int x=0; x < player.width; ++x)//start printing out from the left side of the whole game board
		{
			out<<player.gamespace[(player.width)*y+x].printout<<" "; //once print out one line
		}
		out<<endl; //begin to print from next line
		out<<endl; //print out an empty line
	}
	//print out the x-axis
	out<<"X 0 1 2 3 4"<<endl;
	//return the ostream reference that was passed in
	return out;
}

// This method should return true if there is exactly one almond positioned
//at the center of the board (the square with coordinate 2,2), and all other
//squares are empty; otherwise the method should return false.
bool single_player::done()
{
	bool flag=true;
	for(int i=0; i< width*height; ++i)//check all the positions on the game board
	{
		if(gamespace[i].color!=nocolor)//the current postition has no almond
		{
			if(i!=12)//the current position is not the center postition
			{
				flag=false;
			}
			else//only the center position is allowed to have almond
				continue;
		}
	}
	return flag;
}

//This method should return false if there are any valid moves remaining in the
//game (as defined below) or if the done() method returns true;
//otherwise (if there are no valid moves remaining and the game has not been 
//completed successfully) the stalemate() method should return true.
bool single_player::stalemate()
{
	bool check=is_stalemate(gamespace, 5, 5);
	if(check==true)
		return true;
	else
		return false;

}

//This medthod check every places that have almonds on them and determine
//if there is any neighboring almonds around them. If every almonds (except
//the almond in the center of the game board) all do not have any neighboring
//almonds then it will return true, otherwise it will return false
bool single_player::is_stalemate( const vector<game_piece> &gamespace, unsigned int width ,unsigned int height)
{
	int flag=0;
	for(int i=0; i<static_cast<int>(gamespace.size());++i)
	{
		if(i==12)//only allow that the center almond has no neighboring almonds, i.e. the game is done
		{
			continue;
		}
		else if(gamespace[i].color!=nocolor)//for positions that have chess
		{
			int left=i-1, right=i+1, down=i-width, up=i+width, rightup=i+width+1, rightdown=i-width+1, leftup=i+width-1, leftdown=i-width-1;
			//the left neighbor position is within the board and has a chess in it and it is in the same row with chess[i]
			if(left>=0&&left<static_cast<int>(gamespace.size())&&gamespace[left].color!=nocolor&&(left/width)==(i/width))
				//the neighbor position is within the board and has a chess in it
			{
				flag=1;
			}
			//the right neighbor position is within the board and has a chess in it and it is in the same row with chess[i]
			if(right>=0&&right<static_cast<int>(gamespace.size())&&gamespace[right].color!=nocolor&&(right/width)==(i/width))
			{
				flag=1;
			}
			//the upper neighbor position is within the board and has a chess in it
			if(up>=0&&up<static_cast<int>(gamespace.size())&&gamespace[up].color!=nocolor)
			{
				flag=1;
			}
			//the downside neighbor position is within the board and has a chess in it
			if(down>=0&&down<static_cast<int>(gamespace.size())&&gamespace[down].color!=nocolor)
			{
				flag=1;
			}
			//the rightup neighbor position is within the board and has a chess in it
			if(rightup>=0&&rightup<static_cast<int>(gamespace.size())&&gamespace[rightup].color!=nocolor)
			{
				flag=1;
			}
			//the rightdown neighbor position is within the board and has a chess in it
			if(rightdown>=0&&rightdown<static_cast<int>(gamespace.size())&&gamespace[rightdown].color!=nocolor)
			{
				flag=1;
			}
			//the leftup neighbor position is within the board and has a chess in it
			if(leftup>=0&&leftup<static_cast<int>(gamespace.size())&&gamespace[leftup].color!=nocolor)
			{
				flag=1;
			}
			//the leftdown neighbor position is within the board and has a chess in it
			if(leftdown>=0&&leftdown<static_cast<int>(gamespace.size())&&gamespace[leftdown].color!=nocolor)
			{
				flag=1;
			}
		}
	}
	//after check up all the almonds left on the board and they all have no neighbors
	if(flag==0)
		return true;
	//there is neighboring almond and thus the valid move exists
	else
		return false;
}

//This method will prompt user to type in two pairs of coordintes
//one of them is used as the beginning point of almonds and the
//other one is used as the destination of the almonds
int single_player::prompt(unsigned int & x_ , unsigned int & y_)
{
	string check;
	int flag=0, x_check, y_check;
	cout<<"Type in quit if you want to end the game or type in comma-separated pair of unsigned decimal integers if you want to continue"<<endl;
	while(flag==0)
	{
		cin>>check;//store the type into the string check
		if(check=="quit")
		{
			return quitgame;
		}
		else
		{
			char* index= &check.at(0);
			for(unsigned int i=0;i<check.length();i++) //loop until processing to the end of the string
			{
				if(*index==',' )//check out if the character is comma
				{
					*index = ' ';//convert the comma into space
				}
				index++; //check next character of the string
			}
			istringstream iss (check);//wrap string into a stream
			if(iss>>x_check && iss>>y_check)
			{
				//if both coordinates are within the range of the game board
				if(x_check<=(width-1) && x_check>=0 && y_check<=(height-1)&& y_check>=0)
				{
					x_=x_check;
					y_=y_check;
					flag=1;
				}
				else
					cout<<"Not a valid command. Please type in again (in comma-separated pair of unsigned decimal integers)."<<endl;
			}
		}
	}

	return promptsuccess;
}

//This method is used when the user choose to continue one specific turn
//and gives the user corresponding prompts to just type in the following
//destination without the need to type in the starting point anymore
int single_player::continue_prompt(unsigned int & x_ , unsigned int & y_)
{
	string check;
	int flag=0, x_check, y_check;
	cout<<"Please type in comma-separated pair of unsigned decimal integers as your new destination of current almond."<<endl;
	while(flag==0)
	{
		cin>>check;//store the type into the string check
		char* index= &check.at(0);
		for(unsigned int i=0;i<check.length();i++) //loop until processing to the end of the string
		{
			if(*index==',' )//check out if the character is comma
			{
				*index = ' ';//convert the comma into space
			}
			index++; //check next character of the string
		}
		istringstream iss (check);//wrap string in a stream
		if(iss>>x_check && iss>>y_check)
		{
			//if both coordinates are within the range of the game board
			if(x_check<=(width-1) && x_check>=0 && y_check<=(height-1)&& y_check>=0)
			{
				x_=x_check;
				y_=y_check;
				flag=1;
			}
			else
				cout<<"Not a valid command. Please type in again (in comma-separated pair of unsigned decimal integers)."<<endl;
		}
	}
	return continue_promptsuccess;
}

//This method is used to complete the remove of the original almond
//and the middle almond that it jumped over and place an almond in
//the destination. If any of the requirments is not satisfied the
//method will give users corresponding prompt.
int single_player::turn()
{
	unsigned int x,y,beginx,beginy,endx,endy;
	x=y=0;
	int result = prompt(x, y);
	if(result==quitgame)
	{
		return quitgame;
	}
	else//successfully extract valid coordinates into x and y
	{
		beginx=x;
		beginy=y;
	}

	int result2 = prompt(x, y);
	if(result2==quitgame)
	{
		return quitgame;
	}
	else//successfully extract valid coordinates into x and y
	{
		endx=x;
		endy=y;
	}
	//the continue_flag will be 0 if it is the first turn of an selected almond
	int continue_flag=0;
	//create a vector to record all the tracks one turn has
	vector<int> trackspace;
	while(true)//continue the current turn until the user types in "no"
	{
		if(done()==true)
			return finishgame;
		if(stalemate()==true)
			return stalemategame;
		//calculate the corresponding index stored in the vector space
		int beginpos=((*this).width)*beginy+beginx;
		int endpos=((*this).width)*endy+endx;
		//succesfully get the coordinate of beginning and ending coordinates of piece within the range of game board
		if((*this).gamespace[beginpos].color==brown)//a valid beginning coordinate
		{
			if((*this).gamespace[endpos].color==nocolor)//an empty ending position
			{
				if(endy-beginy==2||beginy-endy==2||beginx-endx==2||endx-beginx==2)//two positions away from the orginal square
				{
					//calculate the middle almond between the start point and the destination
					float middlepos=((float)beginpos+(float)endpos)/2;
					int integral_part = (int)middlepos;
					//check if the middlepos is really a valid middle almond since it could be a float number
					if(middlepos == integral_part)
					{
						middlepos = (int)middlepos;
					}
					//the middlepos is actually not valid and print out the corrsponding prompt to the user
					else
					{
						cout<<"You have typed in an invalid input!(there must be a middle almond)"<<endl;
						cout<<"<< Please retype in your two pair of coordinates from the beginning! >>"<<endl;
						return turnfailure;
					}
					if((*this).gamespace[middlepos].color==brown)//there is an almond on the square that is between the two postions
					{
						if(continue_flag==0)//first turn of an almond and there is no predecent track
						{
							trackspace.push_back(beginx);
							trackspace.push_back(beginy);
							trackspace.push_back(endx);
							trackspace.push_back(endy);
						}
						else//using the same almond to move on and there is no need to store the beginning position
						{
							trackspace.push_back(endx);
							trackspace.push_back(endy);
						}
						//the move is valid and remove the original almond
						(*this).gamespace[beginpos].color=nocolor;
						(*this).gamespace[beginpos].name = "";
						(*this).gamespace[beginpos].printout = " ";
						//remove the middle almond
						(*this).gamespace[middlepos].color=nocolor;
						(*this).gamespace[middlepos].name = "";
						(*this).gamespace[middlepos].printout = " ";
						//place the almond in the ending postion
						(*this).gamespace[endpos].color= stringToEnum("brown");
						(*this).gamespace[endpos].name = "almond" ;
						(*this).gamespace[endpos].printout = 'A';
						//print out the current game board
						cout<< (*this);
						//print out an intervening blank line
						cout<< endl;
						//print out the moves that have been made so far
						int track_index;
						for(track_index=0; track_index<static_cast<int>(trackspace.size()-2); track_index=track_index+2)
						{
							cout<<trackspace[track_index]<<","<<trackspace[track_index+1]<<" to ";
						}
						cout<<trackspace[track_index]<<","<<trackspace[track_index+1]<<endl;
						//ask user if he/she wants to continue					
						while(true)
						{
							if(done()==true)
								return finishgame;
							if(stalemate()==true)
								return stalemategame;
							cout<<"Do you want to continue this turn (yes/no)?"<<endl;
							//check the user's command
							string command;
							cin >> command;
							//at least one turn is completed and the user successfully end this turn
							if(command=="no")
							{
								return turnsuccess;
							}
							else if(command=="yes")//use the current almond as starting postion to put a new place
							{
								//set the continue_flag from 0 to 1 so that the beginning postion of almond will 
								//not be stored in track vector again since it is already known
								continue_flag=1;
								//update the beginx and beginy with the previous ending position of the almond
								beginx=endx;
								beginy=endy;
								//prompt user to type in a pair of numbers to indicate the new destination of current almond
								continue_prompt(x,y);
								endx=x;
								endy=y;
								break;
							}
							else//not a valid input typed in by user
								cout<<"You have typed in an invalid input!"<<endl;
						}
					}
					else
					{
						cout<<"You have typed in an invalid input!(there must be a middle almond)"<<endl;
						cout<<"<< Please retype in your two pair of coordinates from the beginning! >>"<<endl;
						return turnfailure;
					}
				}
				else
				{
					cout<<"You have typed in an invalid input!(wrong distance)"<<endl;
					cout<<"<< Please retype in your two pair of coordinates from the beginning! >>"<<endl;
					return turnfailure;
				}
			}
			else
			{
				cout<<"You have typed in an invalid input!(there is an almond in your destination)"<<endl;
				cout<<"<< Please retype in your two pair of coordinates from the beginning! >>"<<endl;
				return turnfailure;
			}
		}
		else
		{
			cout<<"You have typed in an invalid input!(your start point must have an almond)"<<endl;
			cout<<"<< Please retype in your two pair of coordinates from the beginning! >>"<<endl;
			return turnfailure;
		}
	}
}

//This method is used to continue the game by repeatedly calling
//the turn() method and then the done() and stalemate() methods
//and returns the corresponding value when any of them is satisfied
int single_player::play()
{
	int count,result;
	count=0;
	//print out the game board
	cout<< (*this);
	//repeatedly calls the turn() method and then the done() and stalemate() methods
	while(true)
	{
		//count is used to record the total number of turns
		result=turn();		
		count++;
		//print out the total turns and then return a different unique non-zero failure code
		if(result==quitgame)
		{
			cout<<"You have quit the game after "<<(count-1)<<" turns";
			return quitgame;
			break;
		}
		//print out the total turns and then return a success code (with value 0)
		if(result==finishgame)
		{
			cout<<"You have successfully completed the game in "<<count<<" turns";
			return finishgame;
			break;
		}
		//print out the total turns and then return a different unique non-zero failure code
		if(result==stalemategame)
		{
			cout<<"You have reached at a stalemate in "<<count<<" turns";
			return stalemategame;
			break;
		}
	}
}