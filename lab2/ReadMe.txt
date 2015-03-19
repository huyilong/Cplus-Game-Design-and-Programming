CSE 332 Lab2
Name: Hu Yilong     ID: EN 438033

A. Problems I Met With

1. At the beginning I cannot find out the standard to successfully judge whether the game goes into a stalemate,
and after a series of consideration, I find that it is connected with the "extra credit" task in the last lab 
program and get to know that if every existing almond on the board has no neighbouring almonds, then there is no
valid move further, i.e. the game arrives at stalemate.

2. Firstly, I was struggling with how to determine the different relationships among the various positions on the 
game board, i.e. the conversion between a 2D game board and a 1D vector space. The conversion of the index is quite 
tricky and I listed many different conditions on paper, finally figuring out their relationship and then converting 
my thought into code.

3. When I found that I need to print out all the tracks in the past for one turn, I was confused about how to store 
the former tracks so that they were still there when I printed out them. Eventually, I took advantage of the vector 
space to store all these valid tracks and at the point of printing them out, all I need to do is to print out all the 
data stored in the variable named trackspace.

4. In this very experiment, there are a lot of tasks involving digging into the character within a string. To solve 
this kind of problems, I used many pointer which point to the first character in each element and manipulating the following 
stuffs, such as change the comma in the string into space when reading x and y from the string stream or compare whether 
all the characters in two strings are identical when examining whether the command typed in by users are appropriate.

**5. A very difficult debugging : 
when I do many trials in my program, I surprisingly find that in some cases (for example from <3,2> to <2,4>) even there
is no middle almond between the beginning position and the destination, the move is still regarded as a valid move. This bug
confused me for a very long time because there seems no designing problem in the whole code and in most cases it is running 
smoothly and flawlessly. However, I finally find that in the process of using my index of vector space which is one dimenstion
to determine the index of middle almond, I use division and it will cause severe result since all the variables are integers 
and if the result is not an integer it will be automatically converted to integer and thus cause many miscalculation of the
postion of middle almond. Eventually, I use the code "if(middlepos == integral_part)" to judge whether the postion of middle
almond is really an integer and then carry on the following functions. Things work normally well then.
(Although there is some warnings telling me that thus a conversion might cause loss of some data, I intentionally to do so
that I can check if the integral part of the float middlepos equals itself.)

**6. In the step 5, at the beginning I still cannot get the correct result. After debugging, I find that my original code
float middlepos=(beginpos+endpos)/2; is not working as I intended because the right side of the calculatio are all integers
and it will cause that the result is integer and then it is converted to a float number. This is useless because I want to
get the real result of the middlepos and finally I fix it by change my previous code into the following form:
float middlepos=((float)beginpos+(float)endpos)/2; and it works well.



B. Trials of My Program

Annotation: Based on my designment, if user types in wrong commands in a continuous turn, the program will ask the user to
retype in all the two pairs of coordinates, i.e. it will jump out of the former turn and begin a totally new turn with its
corresponding track.

User-friendly Design: In my program, if the user types in wrong commands, the program will examine the reason why the command
is not correct, i.e. whether it is caused by the wrong beginning position, or there is no middle almond between the beginning
and the destination, or there is already an almond existing in the desitination. Furthermore, the program will inform the user
of the different reasons for the failure of making a valid move and ask the user to retype in the two pairs of coordinates.


Trial 1: Usage Trial

input: lab2.exe ninealmonds
result: print out usage message to ask the user to type in correct usage

input: lab2.exe NineAlmonds
result: successfully log into the game and ready to play

Trial 2: Playing Trial

(a) Successful Completion

M:\hu.yilong\winprofile\desktop\lab2\lab2\Debug>lab2.exe NineAlmonds
4

3   A A A

2   A A A

1   A A A

0

X 0 1 2 3 4
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
2,2
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
2,0
4

3   A A A

2   A   A

1   A   A

0     A

X 0 1 2 3 4

2,2 to 2,0
Do you want to continue this turn (yes/no)?
yes
Please type in comma-separated pair of unsigned decimal integers as your new des
tination of current almond.
4,2
4

3   A A A

2   A   A A

1   A

0

X 0 1 2 3 4

2,2 to 2,0 to 4,2
Do you want to continue this turn (yes/no)?
yes
Please type in comma-separated pair of unsigned decimal integers as your new des
tination of current almond.
2,4
4     A

3   A A

2   A   A

1   A

0

X 0 1 2 3 4

2,2 to 2,0 to 4,2 to 2,4
Do you want to continue this turn (yes/no)?
yes
Please type in comma-separated pair of unsigned decimal integers as your new des
tination of current almond.
0,2
4

3     A

2 A A   A

1   A

0

X 0 1 2 3 4

2,2 to 2,0 to 4,2 to 2,4 to 0,2
Do you want to continue this turn (yes/no)?
no
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
1,1
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
1,3
4

3   A A

2 A     A

1

0

X 0 1 2 3 4

1,1 to 1,3
Do you want to continue this turn (yes/no)?
no
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
3,2
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
1,4
4   A

3   A

2 A

1

0

X 0 1 2 3 4

3,2 to 1,4
Do you want to continue this turn (yes/no)?
yes
Please type in comma-separated pair of unsigned decimal integers as your new des
tination of current almond.
1,2
4

3

2 A A

1

0

X 0 1 2 3 4

3,2 to 1,4 to 1,2
Do you want to continue this turn (yes/no)?
no
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
0,2
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
2,2
4

3

2     A

1

0

X 0 1 2 3 4

0,2 to 2,2
You have successfully completed the game in 4 turns


(b) Game Stalemate
M:\hu.yilong\winprofile\desktop\lab2\lab2\Debug>lab2.exe NineAlmonds
4

3   A A A

2   A A A

1   A A A

0

X 0 1 2 3 4
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
2,2
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
4,2
4

3   A A A

2   A     A

1   A A A

0

X 0 1 2 3 4

2,2 to 4,2
Do you want to continue this turn (yes/no)?
yes
Please type in comma-separated pair of unsigned decimal integers as your new des
tination of current almond.
2,0
4

3   A A A

2   A

1   A A

0     A

X 0 1 2 3 4

2,2 to 4,2 to 2,0
Do you want to continue this turn (yes/no)?
yes
Please type in comma-separated pair of unsigned decimal integers as your new des
tination of current almond.
2,2
4

3   A A A

2   A A

1   A

0

X 0 1 2 3 4

2,2 to 4,2 to 2,0 to 2,2
Do you want to continue this turn (yes/no)?
yes
Please type in comma-separated pair of unsigned decimal integers as your new des
tination of current almond.
2,4
4     A

3   A   A

2   A

1   A

0

X 0 1 2 3 4

2,2 to 4,2 to 2,0 to 2,2 to 2,4
Do you want to continue this turn (yes/no)?
yes
Please type in comma-separated pair of unsigned decimal integers as your new des
tination of current almond.
4,2
4

3   A

2   A     A

1   A

0

X 0 1 2 3 4

2,2 to 4,2 to 2,0 to 2,2 to 2,4 to 4,2
Do you want to continue this turn (yes/no)?
no
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
1,2
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
1,0
4

3   A

2         A

1

0   A

X 0 1 2 3 4

1,2 to 1,0
You have reached at a stalemate in 2 turns

(c) Quit Game

L:\hu.yilong\winprofile\desktop\lab2\lab2\Debug>lab2.exe NineAlmonds
4

3   A A A

2   A A A

1   A A A

0

X 0 1 2 3 4
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
2,2
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
2,0
4

3   A A A

2   A   A

1   A   A

0     A

X 0 1 2 3 4

2,2 to 2,0
Do you want to continue this turn (yes/no)?
no
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
3,2
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
3,0
4

3   A A A

2   A

1   A

0     A A

X 0 1 2 3 4

3,2 to 3,0
Do you want to continue this turn (yes/no)?
no
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
2,0
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
4,0
4

3   A A A

2   A

1   A

0         A

X 0 1 2 3 4

2,0 to 4,0
Do you want to continue this turn (yes/no)?
no
Type in quit if you want to end the game or type in comma-separated pair of unsi
gned decimal integers if you want to continue
quit
You have quit the game after 3 turns
