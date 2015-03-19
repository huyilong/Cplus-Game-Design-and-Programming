/*
File name:boardheader.h

Author:Hu Yilong

E-mail Address: hu.yilong@wustl.edu

Summary: This file includes the declarations of functions named extractGame and readPieces
and a declaration of an empty struct named game_piece.
*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include<sstream>
#include<istream>
#include<fstream>


using namespace std;

//declaration of the struct
struct game_piece;

//declarations of functions for reading information of game board 
int extractGame( ifstream &, unsigned int &, unsigned int &);
//declarations of functions for reading coordinations and information of game pieces from the file
int readPieces( ifstream &, vector<game_piece> &,  unsigned int , unsigned int );
