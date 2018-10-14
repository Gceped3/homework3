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

void doCommand(char **cmd){
  char *file = '\0'; //will hold our filename
  char *io = '\0';   // will tell us the input direction
  char *cmd2 = '\0'; 

  int i = 0;
  while(cmd[i] != '\0'){
    if((strcmp(cmd[i],">") == 0)||( strcmp(cmd[i],"<")== 0)){
      io = cmd[i];    //gets the input/output direction
      file = cmd[i+1];//gets the file name
    }
    if(strcmp(cmd[i],";")==0){
      io = cmd[i];
      cmd2 = cmd [i+1]; //get the second command
      
    }
    i++; 
  }
  if((cmd2 == '\0' || file == '\0') && io == '\0'){
    printf(" Cannot open file or Execute command");
  }
  
  if(strcmp(io, ";") == 0){
    printf("%s %s %s \n",cmd[0], io, cmd2);
  }
  if(strcmp(io,"<") == 0|| strcmp(io,">")==0){
    printf("%s %s %s \n", cmd[0],io, file);
  }
  
  int pid = fork(); 
  if(pid == 0){
   //do nothing yet...

  }
  else{
    int status;
    wait(&status);
    printf("pid: %d status: %d \n", pid, WEXITSTATUS(status)); 
  }
}

void sigint_handler(int sig){
  char msg[] = "\ncaught sigint\n";
  write(1,msg, sizeof(msg));
  char prompt[] = "CS361 >";
  write(1, prompt, sizeof(prompt));
}

void sigstp_handler(int sig){
  char msg[] = "\ncaught sigtstp\n";
  write(1,msg, sizeof(msg));
  char prompt[] = "CS361 >";
  write(1, prompt, sizeof(prompt));
  //Don't think it needs to do anything else? Infact it doesn't need to stop either.
}

int main(){
  //Input storage
  char line[500]; //Going based off of Lab 4 
  char *argsarray[20];

  //signals based on lab 5 code
  signal(SIGINT, sigint_handler);
  signal(SIGTSTP, sigstp_handler);//prompt said sigstp but that didn't work

  while(1){ //infinite loop until we need to exit the program
   
    printf("CS361 > "); //NEEDS to print out exactly like this

    fgets(line, 500, stdin); //read input
    char *word = strtok(line, " \n");//reads line until newline character, Also the space matters
    int i = 0;
    while(word){
    //  printf("word: %s\n", word);
      
      argsarray[i]= word;
      word = strtok(NULL, " \n");//sets word to NULL to be copied over again
      i++;
    }

    if(strcmp(argsarray[0],"exit")== 0){
      break;
    }
    
    doCommand(argsarray);
  }
	
  return 0;
}
