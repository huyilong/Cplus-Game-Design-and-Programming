// lab0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lab0head.h"//include the head file which created by myself
#include<iostream>
#include<sstream>
#include<istream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
enum Retval extractString( vector<string> &, char *);//declare the function
enum Retval message(char* );

int main(int argc, char* argv[])
{
	vector<string> strspace;
	vector<int> intspace;
	enum Retval result;
	if(argc!=requirenum)//the number of commands is wrong and return fail
	 {
          return message(argv[proname]);
	 }
	else//the number of commands is correct and continue
	 {
	  result=extractString(strspace, argv[filename]);
	  if(result!=success)//cannot extract strings from the file and return fail
     	{
			cout << "encountered error " << result << endl;
			getchar();
			return result;	
	    }
      else//successfully extract strings from the file and continue
	    {
			cout<<"The lines which contain non-digit characters are shown as following:"<<endl;
			for(size_t s=0; s<strspace.size(); ++s)	
		    {
			int flag=1;//set the flag to avoid repeatedly storing the digital string
			char* inspect; //create a pointer to point to the first character in each string
			inspect = &strspace[s].at(0);
			while(*inspect!='\0'&&s<strspace.size()) //loop until the last character checked by the pointer
			  {			
		     	if(isdigit(*inspect)==0)//once the string contains non-digit, print it out
				{
				  cout<<strspace[s]<<endl; //there is no need to check following chars because there is already one non-digit found
				  if(s==(strspace.size()-1))//get out of the while-loop if it is the last string, otherwise the subscript "s" will exceeds the max size of string vector
				  {
					 flag=0;//the last string contains non-digit characters and is already printed out
					 break;
				  }
				  else
				  {
				      ++s; //move to next string in the vector space
				      inspect=&strspace[s].at(0); //set the pointer to point to the first character in next string 
				  }
				}
				else
				inspect++;//inspect the following character in the string
		     	}  
			//store the string into integer vector if the string has not been printed out yet
			    if(flag)
				{
				  //the string is digital
				   istringstream argsin(strspace[s]); 
				   int convert;
			       argsin>>convert;//convert the string to integer
			       intspace.push_back(convert);
				}
			
			}	 
            //print out all elements in the integer space
		    cout<<"The all-digit lines are shown as following:"<<endl;
			for(size_t ss=0; ss<intspace.size();++ss)
			   {
				cout<<intspace[ss]<<endl;
			   }
			return success;
		}
	}
}

enum Retval message(char* name)//when the number of commands typed in by user is wrong, print out the message and return fail
{
	cout<<"usage:"<<" lab0 <input_file_name>"<<endl;
	return fail;
}

enum Retval extractString(vector<string> &line, char * filename)//extract the strings from file to the string vector
{
	string container; //read string from the file into container
	ifstream ifs;
	ifs.open(filename);
	if(ifs.is_open())//continue if the file is opened successfully
	{
		 while(ifs>>container)//get all the strings from the file till the end
		 {  	 
			 line.push_back(container);		 
		 }
         return success; 
	}
	else
		return fail; //file cannot be opened and return fail
}