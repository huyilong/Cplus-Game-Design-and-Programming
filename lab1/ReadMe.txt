
Lab1  Yilong Hu  ID:438033

a. I ran into the following errors while I am developing my solution.

   (1) In the beginning, I am not familiar with the use of  enum. GetName ( typeof( piece_color ), value);    
       and (piece_color) enum.Parse(typeof(piece_color), nocolor);
       The compiler complains about the use of "enum."
       
       To handle this mistake, I find that the enum. GetName() is actually not supported in C++ but in .Net
       And then I used the "if" to check out the commands and return different values of type enumeration

   (2) In the process of programming, I did not notice that if at least one of the lines is extracted successfully to           
       define the values of game pieces, the program should read it and anyway print out the whole game board. 
       In such case, whenever my program meets non-well-formed lines it will stop running.

       To solve this problem, I set a flag variable which has an initialzing value 0. The ifstream will then ignore 
       all non-well-formed lines until the end of the file. In this process, if there is even one line which is 
       well-formed, the flag will change its value to 1, and then the program will further print out the game board.

  *(3) It is a concept mistake and results in many troubles in my program:

       After I delaration my enum piece_color, I should not add the key word "enum" whenever I use the new type I 
       defined as "piece_color". In the beginning I did not know that and the compiler always complains about the
       "enum" I used. More importantly, after the initialization of enumeration, we should use int as the type of 
       the value grouped in such an enumeration.

 **(4) Important Warning: In my extracredit programming, I cannot directly compare unsigned values with signed values!

       In my functions, especially in my extracredit function, I used a lot of comparisons to make sure if the neighbors
       of the current checker have checkers. However, the type of gamespace.size() is a unsigned type value and thus 
       cannot be compared directly with other signed variables, Therefore I used the method: static_cast<int> to successfully
       convert unsigned variables into signed ones and then I can successfully compare them and complete my extracredit function.
 
 **(5) Important Difference: C++ does not support switch string!

       At first, I tried to switch the string to deal with the function: piece_color stringToEnum(string str)
       However, I find that the compiler will not let me do such a thing because the C++ language does not support
       the switch over string type variables. It is a big difference from JAVA and C#.

        
       
       

b.Running result of executable program (Trial 3 and Trial 4 including my Extra Credit running resultS)

Trial 1:
usage: lab1 checkers.txt

result:

 O O O O
O O O O
 O O O O


X X X X
 X X X X
X X X X

conclusion: It is a proper behavior

Trial 2:
usage: lab1 chess.txt

result:

rsbqkbsr
pppppppp




PPPPPPPP
PSBQKBSR

conclusion: It is a proper behavior

Trial 3:
usage: lab1 extra_credit1.txt

result:

   #

xo
xo

0,0 black checker: 1,0 red checker; 0,1 black checker; 1,1 red checker;
1,0 red checker: 0,0 black checker; 1,1 red checker; 0,1 black checker;
0,1 black checker: 1,1 red checker; 0,0 black checker; 1,0 red checker;
1,1 red checker: 0,1 black checker; 1,0 red checker; 0,0 black checker;
3,3 white checker: has no neighboring checkers

conclusion: It is a proper behavior

Trial 4:
usage: lab1 extra_credit2.txt

result:

R
  K
 KPB
 BK
PQ

0,0 white pawn: 1,0 red queen; 1,1 black bishop;
1,0 red queen: 0,0 white pawn; 1,1 black bishop; 2,1 black king;
1,1 black bishop: 2,1 black king; 1,2 black king; 1,0 red queen; 2,2 white pawn; 0,0 white pawn;
2,1 black king: 1,1 black bishop; 2,2 white pawn; 3,2 black bishop; 1,2 black king; 1,0 red queen;
1,2 black king: 2,2 white pawn; 1,1 black bishop; 2,3 black king; 2,1 black king;
2,2 white pawn: 1,2 black king; 3,2 black bishop; 2,3 black king; 2,1 black king; 1,1 black bishop;
3,2 black bishop: 2,2 white pawn; 2,3 black king; 2,1 black king;
2,3 black king: 2,2 white pawn; 3,2 black bishop; 1,2 black king;
0,4 white rook: has no neighboring checkers

conclusion: It is a proper behavior

c.Design and Completion of Extra Credit programming

First, I find that the y-axis coordination can be calculated by the index of the checker in vector divided by 
the width of the game board and the x-axis coordination of the game board can be calculated by using index
mod the width of the game board.

With the coordinations of the checker, I further calculated the neighboring checkers of current checker, and 
constricted that the coordinations of these neighboring checkers should be within the range of the game board.
In addition, the left or right neighboring must be within the same row with the current checker.

I set a flag which may indicate whether the current checker has neighboring checkers, and if there is even one
neighbor, print it out, otherwise print out that "has no neighboring checkers".

Annotation: the running condition and the corresponding results of Extra Credit is included in part b, i.e. the 
Trial 3 and Trial 4.