//Jessenia Lopez - Lecture 15
#define MAXARG 50 //max number of commands to be supported
#define MAXCHAR 1024 //Max number of letters in arg
//#define MAXNAME 500 //max number of chars in a file name

void type_prompt();
void greeting();
void jss_readcommand( char cmd[], char *par[] );
int jss_help( char *par[] );
int jss_cd( char *par[] );
int jss_execute( char cmd[] , char *par[] );
int jss_launch( char cmd[], char *par[] );