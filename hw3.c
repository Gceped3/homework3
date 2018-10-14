/* George Cepeda 
*  cs361
*  Due:10/18/18 <- changed from 10/15/18
*  Homework 3 Create a Shell
*/


//Based on labs 4-5 these includes will be needed.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <fcnt1.h>
#include <unistd.h>

int main(){
  //Input storage
  char line[500]; //Going based off of Lab 4 
  char argsarray[20][100];

  while(1){ //infinite loop until we need to exit the program
   
    printf("CS361 > "); //NEEDS to print out exactly like this

    fgets(line, 500, stdin); //read input
    char *word = strtok(line, "\n");//reads line until newline character
    int i = 0;
    while(word){
      strcpy(argsarray[i], word);
      word = strtok(NULL, "\n");//sets word to NULL to be copied over again
      i = i + 1;
    }

    if(strcmp(argsarray[0],"exit")== 0){
      break;
    }
  
  }
	
  return 0;
}
