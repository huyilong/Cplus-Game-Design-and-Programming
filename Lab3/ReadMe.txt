Graded by: Justin Zheng (justin.zheng@wustl.edu)
Score: 99/100 (94 +5 Extra Credit)
Comments:

Comments in code are prefixed with "JZ:"; you can do a project-wide search for those if you want.

= note that in pretty much everything these days it's safe to use #pragma once to arrive at the same
effect as include guards. 
= good documentation in your readme! 
= interesting how often you use strcmp and c_str() on C++ strings; the operator== works just fine on those
y'know :0
-2 '0' error code is given for stalemates as well as victories in both games
-1 usage message should not have program name hard-coded
-1 your return_values enum ends up being redundantly defined in each .cpp file; it should've been
declared in some common header file (like a new 'CSE332_Lab3.h') instead to improve modularity
and avoid repetition.
-2 there are many magic numbers peppered throughout your code; try to give these variable names
	or #define them, (see the style guide for more advice on this). With indexing in argv and 
	checking argc in particular, you can use an enum that gives labels to those arguments/values

-------------------------------------------------------------

CSE332 Lab3
Yang Ye    ye@go.wustl.edu
Yilong Hu  hu.yilong@go.wustl.edu  
Chao Zhang zcvictory0329@gmail.com

A. Work Assignment:
The NineAlmondGame was based on Yang Ye's previous lab. He wrote half of the GameBase class which was used for NineAlmondGames, and he revised his previous lab to finish NineAlmond part of this lab.
Chao Zhang and Yilong Hu worked together on the MagicSquare part. They wrote another part of the GameBase Class which was used for MagicSquare.
We worked together on the extra credit and debugging of the lab.    

B. Problems We Met:
1. Because there are two classes which will inherit the same base class, we need to include the header of base class. However, the compiler always informs us of the mistake of redefinition since we have include the same header twice.
Solution:
To solve this problem, we use the following codes:
#ifndef HEADER_H_
#define HEADER_H_
#endif
The code above is used to check if a header is included repeated and automatically avoid the mistake. In this way, we solve the problem.

2. In the process of coding, we always ran into the bug that “ a type of value cannot be assigned into a type of entity “ when we use the “new” code to construct a new object of “NineAlmondsGame” or “MagicSquareGame” and assign it to a “GameBase” type pointer.
Solution:
It is a really difficult debugging because according to the mistake hint we cannot figure out why our “NineAlmondsGame” or “MagicSquareGame” become types of value. After our discussion and checking, we find that it is caused by that we redefined the class, i.e. we repeatedly include the same header file. Knowing that, we successfully solved this problem  by the solution to our problem 1.

3. In the Extra Credit Task, we find that the available pieces should be considered into different cases so that it will be printed out according to the different minimum of starting point typed in by the users.
Solution:
After our discussion and the calculation on the paper, we find that if the user typed in a negative number or zero as starting point, then the maximum should be 1 less than the original maximum because in this case “0” also occupies a valid position. And if the user typed in a positive number as starting point, then the maximum should be calculated as before. Therefore, we successfully solved the problem.

4. In the process of coding, we ran into a problem that when we used “new” to create a new object of our subclass, i.e. “NineAlmondsGame” or “MagicSquareGame”. The compiler told us that it failed to do so.
Solution:
We found that if we want to create a new object of our class we must override all the virtual functions in our base class. If we failed to do so, the class actually is a “virtual” class and therefore cannot be created with “new” command.

5. When we programmed by using the setw() function, we got confused because it was always printed out problematically. The width between the numbers is very weird and we do not know why it is printed in this way.
Solution:
After we looked it up via Internet, we found that the setw() function will set the number of characters to be used as the field width for the next insertion operation rather than the space between two numbers. Therefore, we calculated the according formula to determine the right width and successfully solved this problem.


C. Testing and Results:
enum return_value{success=0, fail=1, wrongGameName=2, too_many_input=3, not_enough_input=4, unable_to_read_coordinate=5, invalidMove=6, stalemateOccured=7, ninealmond_user_quit=8, magicsqure_user_quit=9, bad_Alloc=10,unkown_exception=11, other_exeception=12};

1. Test of NineAlmondsGame:
 Test 1:
 Input: CSE332_Lab3
 Output: usage: usage:CSE332_Lab3 arg1 arg2 arg3 or type CSE332_Lab3 -h for help
 return value: 4

 Test 2:
 Input: CSE332_Lab3 as
 Output: usage: usage:CSE332_Lab3 arg1 arg2 arg3 or type CSE332_Lab3 -h for help
 return value: 2

 Test 3:
 Input: CSE332_Lab3 as fd er as f
 Output: usage: usage:CSE332_Lab3 arg1 arg2 arg3 or type CSE332_Lab3 -h for help
 return value: 3

 Test 4:
 Input: CSE332_Lab3 NineAlmonds
 we give a coordinate 6,6 that is out of our gameboard, then we give another coordinate 0,0. The program will print out the move
 is invalid, please try another move. Then we can type new coordinate to try again. The program will not terminate unless you type quit. 

 Test 5:
 Input: CSE332_Lab3 NineAlmonds
 we give a coordinate 2,2, then we give another coordinate 0,0. The program will print out the new gamestate, and ask us to continue this turn or not.
 we type n. Then the program ask me for a new coordinate or to quit. we type quit. The program terminates, and it tells us how many moves we have used so far.
 Rerturn value: 8

 Test 6:
 Input: CSE332_Lab3 NineAlmonds
 I give coordinate 2,2 and 2,0, then program prints out the new game state. Then I type y to continue the turn. Then the program ask me for a new coordinate
 to continue this turn. I type 4,2, the program prints out the new game state. Then we keep playing, here is the moves that leads me to win.
 Turn 1: 2,2 to 2,0 to 4,2 to 2,4 to 0,2
 Turn 2: 3,2 to 1,4
 Turn 3: 1,1 to 1,3
 Turn 4: 1,4 to 1,2
 Turn 5: 0,2 to 2,2
 At the last turn, We type n to not continue the turn, the program indicates we win and we used 5 turns.
 Return value: 0
 
 Test 7:
 Input: CSE332_Lab3 NineAlmonds
 Here is a move we make the game to a stalemate. 
 Turn 1: 2,2 to 0,0
 Turn 2: 2,1 to 4,1
 Turn 3: 2,3 to 4,3 to 2,1 to 0,3 to 2,3
 At last turn, We type n to not continue and the program says a stalemate occurs and we used 3 turns.
 Return value: 7


2. Test of MagicSquare:
 Test 1:
 Input:CSE332_Lab3 -h
 Output:
  usage: CSE332_Lab3 arg1 arg2 arg3

  arg1  - Name of the games: NineAlmonds or MagicSquare   
          e.g CSE332_Lab3 NineAlmonds

  arg2  - (Optional) You can choose the size of the game board in MagicSquare   
          e.g CSE332_Lab3 MagicSquare 6

  arg3  - (Optional) You can choose the size of the game board and the starting number in MagicSquare 
          e.g CSE332_Lab3 MagicSquare 6 -2

 return Value:0

 Test 2:
 Input: CSE332_Lab3 MagicSquare
 The Game enters sucessfully, and it prints out a 3X3 gameboard and correct available game pieces numbers which are 1 to 9. We randomly give a sequence of inputs which will lead the game to stalemate.
 Return Value:7

 Test 3:
 Input: CSE332_Lab3 MagicSquare a
 Output:usage: usage:CSE332_Lab3 arg1 arg2 arg3 or type CSE332_Lab3 -h for help
 Return Value: 1

 Test 4:
 Input: CSE332_Lab3 MagicSquare 5
 The Game enters sucessfully, and it prints out a 5X5 gameboard and correct available game pieces numbers which are 1 to 25. We randomly give a sequence of inputs which will lead the game to stalemate.
 Return Value: 7

 Test 5:
 Input: CSE332_Lab3 MagicSquare 5 4
 The Game enters sucessfully, and it prints out a 5X5 gameboard and correct available game pieces numbers which are 4 to 29. We randomly give a sequence of inputs which will lead the game to stalemate.
 Return Value: 7

 Test 6:
 Input: CSE332_Lab3 MagicSquare 7 -3
 The Game enters sucessfully, and it prints out a 5X5 gameboard and correct available game pieces numbers which are -3 to 45. We randomly give a sequence of inputs which will lead the game to stalemate.
 Return Value: 7

 Test 7:
 Input: CSE332_Lab3 MagicSquare 3 1
 The Game enters sucessfully, and it prints out a 3X3 gameboard and correct available game pieces numbers which are 1 to 9. We go to wikipedia find a solution for this magic square. The solution gives us a correct result.
 Return Value: 0

 Test 8:
 Input: CSE332_Lab3 MagicSquare 5 1
 The Game enters sucessfully, and it prints out a 5X5 gameboard and correct available game pieces numbers which are 1 to 25. We go to wikipedia find a solution for this magic square. The solution gives us a correct result.
 Return Value: 0

 Test 9:
 Input: CSE332_Lab3 MagicSquare 5 1
 The game enters sucessfully, and it asks us to enter a coordinate or type quit. This time, we just type quit. The game terminate and prints "Successfully quit!".
 Return Value: 9

 
Extra Credit:
Implementation:
The extra credit is very similar to the regular MagicSquare. We add two more constructors in the MagicSquare class. The first constructor only takes one input, which is the size of the gameboard. Once the constructor gets a valid
gameboard size n, it will create a nxn gameboard. This gameboard is a nXn string type vector. Moreover, we have an vector which stores all the available gamepiece. For this constructor, our gamepiece are 1 to nXn. Then all the other things
are the same to the regular 3X3 MagicSquare. When the user fills all the positions of the gameboard, we will add all numbers on vertical and horizonatal and see whether they are all equal. If so, the user wins. Otherwise a stalemate occurs.
The next part of the extra credit is just add a starting number of the gamepieces. We ask one more input in the constructor. Then the gamepiece vector will pushback the starting number that user gives. However, sometimes the user will give a
negative number or a number larger than 1. This is easy to solve. For negative number let's say m, the gamepieces will be m to nXn -|m| -1.(0 is included). For number that larger than 1 let's denote i, the gamepieces are i to nXn-i. All the other
things will be same to the previous condition.  


========================================================================
    CONSOLE APPLICATION : CSE332_Lab3 Project Overview
========================================================================

AppWizard has created this CSE332_Lab3 application for you.

This file contains a summary of what you will find in each of the files that
make up your CSE332_Lab3 application.


CSE332_Lab3.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

CSE332_Lab3.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

CSE332_Lab3.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named CSE330_Lab3.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////

 



 




 
 

