Lab0  Yilong Hu

a. I ran into the following errors while I am developing my solution.

   (1) At first, I could not use the char pointer to point to a string in vector space.
       i.e. char* inspect=&strspace[s]; cannot work

       Finally I use the at() method to solve this problem
       i.e.  char* inspect=&strspace[s].at();
 
   (2) At first, I did not add "else" after the sentence if(argc!=requirenum) and if(result!=success).
       The error is that each method could only return one value at one time. 
       If I do not use "else", the main() method will return mutiple values at one time, which is not allowed.

   (3) When I check out if there is non-digit element in the string, I did not add "++s;" and 
       "inspect=&strspace[s].at(0);" at the beginning.
       This error caused that once there is a non-digit found by the "while" sentence, it would print out the 
       same string again. 

  *(4) It is a really difficult slight mistake:
       I forgot to add if(s==(strspace.size()-1)){break;} in my program at the beginning, and it caused that my 
       subscript "s" of vector always exceeds the max size of the vector because s++ twice in two loops.

 **(5) Another very difficult slight mistake:
       I forgot to set the "flag" in my loop at the beginning, and it caused that when the last string is non-digit
       it will get out of the loop and restore the former digital string again, which already exits in the vector. It 
       takes a lot of time for me to figure out why the last dightal string printed out twice before I fix it. 


b. The process of operating my program:

   (1) command line: 
	lab0 file1.txt

       result:
	The lines which contain non-digit characters are shown as following:
 	Hello
	world
	!
	I
	am
	Hu	
	Yilong.
	I
	major
	in
	computer	
	science.
	hellooooo
	The all-digit lines are shown as following:
	20
	123123

       conclusion: It is correct behavior.

   (2) command line: 
	lab0 file2.txt

       result:
	The lines which contain non-digit characters are shown as following:
	Yilong	
	Hu
	this
	is
	lab
	I
	am
	in
	cse
	The all-digit lines are shown as following:
	1234
	5678
	332

       conclusion: It is correct behavior.

   (3)
       after using step( 2 ) or step( 1 ):

       command line: echo %errorlevel%

       result: 0

       conclusion: It is correct behavior.


   (4)
   
       command line: 
         lab0
       result:
         usage: lab0 <input_file_name>
      
       command line:
         echo %errorlevel%

       result: 1
       conclusion: It is correct behavior.


********** Extra Credit

   1.SSH Secure Shell 3.2.9 (Build 283)

Copyright (c) 2000-2003 SSH Communications Security Corp - http://www.ssh.com/

This copy of SSH Secure Shell is a non-commercial version.
This version does not include PKI and PKCS #11 functionality.


This system is now WUSTL Key enabled.

Last login: Tue Sep  9 10:44:33 2014 from urb222-16.seasad.wustl.edu


   2. The warnings I encountered in the process

[hu.yilong@shell lab0]$ make lab0
g++ -o lab0 -DUNIX   -Wall -W -g -pedantic lab0.cpp -lnsl
lab0.cpp:84:13: warning: unused parameter ânameâ [-Wunused-parameter]
 enum Retval message(char* name)//when the number of commands typed in by user is wrong, print out the message and return fail
             ^

   I fix this problem by deleting the unused parameter "char* name" and making corresponding changes in the declaration of the function.

   Then it works well as following:
[hu.yilong@shell lab0]$ make lab0
g++ -o lab0 -DUNIX   -Wall -W -g -pedantic lab0.cpp -lnsl




   3. The result of running my program on Linux is shown as following:

[hu.yilong@shell lab0]$ ./lab0 file1.txt
The lines which contain non-digit characters are shown as following:
Hello
world
!
I
am
Hu
Yilong.
I
major
in
computer
science.
hellooooo
The all-digit lines are shown as following:
20
123123

[hu.yilong@shell lab0]$ ./lab0 file2.txt
The lines which contain non-digit characters are shown as following:
Yilong
Hu
this
is
lab
I
am
in
cse
The all-digit lines are shown as following:
1234
5678
332


