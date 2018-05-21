//Jessenia Lopez - Lecture 15
#include <sys/wait.h> //for fork and wait
#include <stdio.h> //for NULL
#include <string.h> //for strcpy
#include <unistd.h> //for execve
#include <stdlib.h> //for exit()
#include "shell_functions.h"

int main(void) 
{
	char cmd[100], command[100], *param[20];
	char *envp[] = { (char *) "PATH=/bin", 0 }; //defines environment variables

	while (1)
	{
		
		type_prompt(); //displays prompt on the screen
		jss_readcommand(command, param); //read input from terminal
		
		if ( strcmp(command, "exit") == 0 ) //if command is exit
			exit(0); //breaks the loop

		if ( fork() != 0 ) //parent
			wait (NULL); //wait for child
		
		else 
		{
			strcpy(cmd, "/bin/"); //copies the bin directory to the empty array
			strcat(cmd, command); //concatenates the command the user has entered
			execve(cmd, param, envp); //execute command
		}
		
	}
return 0;
}