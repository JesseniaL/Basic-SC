//Jessenia Lopez - Lecture 15
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "shell_functions.h"

//Lists the commands that are built-in
char *built_str[] = {
  "cd",
  "help"
};

//Transitioning to built-in commands
int (*built_func[]) (char **) = {
  &jss_cd,
  &jss_help
};

//Counts how many built-in functions I have
int jss_numofbuiltstr() {
  return sizeof(built_str) / sizeof(char *);
}

//System Command is Executed
int jss_launch( char cmd[], char *par[] )
{
	//printf("In jss_launch...\n");
	
	pid_t pid; //pid_t pid, wpid;

	pid = fork(); //Forking a child

	if (strcmp(&cmd[0], "exit") == 0)
    	exit(0);
	
	// Child process
	if (pid == 0) 
	{
		//printf("Child pid=%d.\n", getpid());
		
		if (execvp(cmd, par) == -1) // Could not execute the command if less than 0
			perror("jss: Command cannot be executed...\n"); //change to jss
		exit(0);
	
	}
	
	// Forking error (failed to fork)
	else if (pid < 0) 
	{
		perror("Forking ERROR...\n"); //change to jss
	}

	// Parent process
	else 
	{
		/*do 
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));*/
		wait(NULL); //Waiting for the child to terminate
		
		//pid_t childpid=waitpid(pid, NULL, WNOHANG);	
		//printf("Waiting for child pid=%d to terminate.\n", childpid);
		//exit(0);
	}

return 1;
}

//Executes User Commands
int jss_execute( char cmd[], char *par[] ) 
{
	//printf("In jss_execute...\n");

	// An empty command was entered.
	if (strcmp(&cmd[0], "exit") == 0)
	{
		printf("In jss_execute if statement...\n");
    	exit(0);
	}
	
	if (&cmd[0] == NULL)
    	return 1;

 	for (int i = 0; i < jss_numofbuiltstr(); i++) 
 	{
 		//if (strcmp(par[0], built_str[i]) == 0) {
  		if (strcmp(&cmd[0], built_str[i]) == 0) 
  		{ 
  			return (*built_func[i])(par); 
   		}
  	}
  //return jss_launch(par);
  jss_launch(cmd, par); 
  //execvp("exit", NULL);
return 0;
  
}

//cd Command
int jss_cd( char *par[] )
{
	if (par[0] == NULL)
    	fprintf(stderr, "jss: expected argument to \"cd\"\n");
  	
  	else if (chdir(par[1]) != 0) 	
  		perror("jss "); //The directory does not exist 
    
    else
    {
    	chdir(par[1]); //changes the directory
    	printf("Inside the directory: %s", par[1]);
  	}

  	printf("\n");
return 1;
}

//help command
int jss_help(char *par[])
{
	printf("\t________________________________________________");
	puts("\n\t|Use the jss shell at your own risk...\t\t|"
        "\n\t|List of commands supported are the following:  |");

	printf("\t|\t\t exit\t\t\t\t|\n\t|\t\t ls\t\t\t\t|\n\t|\t\t echo\t\t\t\t|\n\t|\t\t clear\t\t\t\t|\n\t|\t\t rm\t\t\t\t|\n\t|\t\t man\t\t\t\t|\n\t|\t\t mkdir\t\t\t\t|\n\t|\t\t rmdir\t\t\t\t|\n");

	for( int i=0; i<jss_numofbuiltstr() ; i++)
	{
		printf("\t|\t\t %s\t\t\t\t|\n", built_str[i]);
	}
	printf("\t|_______________________________________________|\n\n");

return 1; 
}

void jss_readcommand(char cmd[], char *par[]) //returns the command and parameters
{	
	char line[MAXCHAR];
	int count=0, i=0, j=0;
	char *array[MAXARG], *ltk;

	//Read one line
	for ( ;; )
	{
		int c = fgetc(stdin); //gets user's input
		line[count++] = (char) c;
		if ( c=='\n' ) //until return is entered
			break; //we exit the loop
	}

	if ( count==1 )
		return;
	ltk=strtok(line, " \n"); //line is being broken down into tokens

	//Parse the line into words
	while ( ltk!=NULL ) 
	{
		array[i++] = strdup(ltk); //tokens are being placed into the array
		ltk = strtok(NULL, "\n");
	}

	//First word == command
	strcpy(cmd, array[0]);
	//printf("cmd = %s\n", cmd);


	//Parameters
	for(int j=0; j<i; j++)
		par[j] = array[j];

	
	//Directs to built-in functions
	jss_execute(cmd, par);

  	par[i]=NULL; //NULL terminates the parameter list, and is being returned
}

void type_prompt()
{
	static int first = 1;
	if (first) //creates a screen
	{
		const char* CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J"; //"{2J" created the screen
		write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);
		first = 0;
		greeting();
	}
	printf("Jessenias-Simple-Shell@root$ "); //display prompt
}

void greeting()
{
	printf("Welcome to My Shell!\n");
	char *usern = getenv("USER");
	printf("@%s", usern);
	printf("\nFor help, write 'help'");
	printf("\nTo leave the shell, write 'exit'\n");
	printf("________________________________\n");
}