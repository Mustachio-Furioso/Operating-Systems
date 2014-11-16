/*****************************************************
* Edgar Sias -  z1707589
* assignment02
* Due date: 9/26/14
* Date: 9/25/14
* This program simulates a bash shell
*****************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/types.h>
#include <stdio.h>

using namespace std; 

void noWhiteSpace(string &str);
void separate(string fullStr, vector<string> &vec, char delim);

int main()
{
  string buffer; //buffer contains input line
  //command = strings separated by ; 
  // oneword = commands separated by " " 
  // history contains all commands so far
  vector<string> commands, oneword, history;
  int stat1 = 0, counter = 1; //stat1 for the wait function, counter for history
  pid_t pID; //integer for fork
  
  do
  {
    cout << "mysh-" << counter << ": ";
    getline(cin,buffer);
    separate(buffer,commands,';');
    
    for(unsigned i = 0; i < commands.size(); i++)
    {
      separate(commands[i],oneword,' '); //separate each command by individual words

      while(oneword.size() < 6) //pads vector
        oneword.push_back("");  //to avoid out of bounds exception

      if(oneword[0] == "quit" && oneword[1] == "") //if user entered quit
      {
        counter = -1; //break while loop
        break; //break for loop
      }
      else if(oneword[0] == "history" && oneword[1] == "") //if user entered history
      {
        history.push_back(oneword[0]); //add command to history
        for(unsigned it = 0; it < history.size(); it++) //display vector containing history
          cout << it+1 << ": " << history[it] << endl;
      }
      else //if the command is not quit or history
      {
        if( (pID = fork() ) == 0) //if forked child process
        {
          char* argv[8]; //will hold arguments passed to execvp, copied from oneword
          unsigned it = 0, it2 = 0; //iterator to go through oneword
          for(it = 0; it < oneword.size() ; it ++) //copies oneword strings into argv char* array
          {
            if(oneword[it] != "")
            {  argv[it2] = (char *)oneword[it].c_str(); 
               it2++;
            }
          }
          argv[it2] = 0; //adds a null to the end of argv 
          
          execvp(argv[0],argv); //execute command
          perror(argv[0]);
          exit(1);
        }
        else if(pID < 0) //if fork failed
        {
          cerr << "Fork failed!\n";
          exit(1);
        }
        else if(pID > 0) //if parent
          wait(&stat1); //wait for child to finish
        history.push_back(commands[i]); //add command to history
      }
      counter++; //increment counter
    }
  }while(counter > -1);

  return 0;
}

/*************************************
* Takes in a string and deletes any leading spaces
*************************************/ 
void noWhiteSpace(string &str)
{
  while(str[0] == ' ') //while the first character is a space
  str = str.substr(1,str.size()-1); //remove it from the string
}

/*************************************
* Takes in a string, separates it by delimiter delim,
*  then it adds each substring into provided vector
*************************************/
void separate(string fullStr, vector<string> &vec, char delim)
{
  vec.clear();
  size_t found = fullStr.find(delim); //location of first delimiter
  string subStr; //string to hold parsed string, returns npo if not found
  
  while(found != string::npos) //while a delimiter is found
  {
    subStr = fullStr.substr(0,found); //subString = start of fullStr to delimiter
    vec.push_back(subStr); //add parsed string to vector

    fullStr.erase(0,found+1); //trim fullStr  to exclude parsed string
    fullStr = fullStr; //reset locations of fullStr by setting it to itself

    noWhiteSpace(fullStr); //remove leading spaces from fullStr
    found = fullStr.find(delim); //find next delimiter
  }
  noWhiteSpace(fullStr); //remove leading spaces from fullStr
  if(fullStr != "") //in case the delimiter is the very last character (null string after ^ )
    vec.push_back(fullStr); //add final parsed string to vector
}


