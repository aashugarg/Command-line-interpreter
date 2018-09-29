#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX_SIZE 512
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define BOLD "\033[1m"


char** tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i <= strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\0' || readChar == '\t'){
        token[tokenIndex] = '\0';
        if (tokenIndex != 0){
	        tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	        strcpy(tokens[tokenNo++], token);
	        tokenIndex = 0; 
        }
    } else {
        token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}


int main()
{
    char str[MAX_SIZE];
    char **myargs;
    while(1)
    {
        printf(BOLD ANSI_COLOR_BLUE "prompt> " ANSI_COLOR_RESET);
        fgets(str, MAX_SIZE, stdin);
        str[strlen(str)-1] = '\0';
        char *commands[100];
        char *token = strtok(str, ";");
        int i;
        for(i=0; token!=NULL; ++i)
        {
            commands[i]=token;
            token=strtok(NULL, ";");
        }
        commands[i]=NULL;

        
        for(i=0; commands[i]!=NULL; ++i)
        {
            myargs = tokenize(commands[i]);
            if(myargs[0]!=NULL)
            {
                if(!strcmp(myargs[0],"quit"))
                {
                    exit(0);
                }
                /*else if (!strcmp(myargs[0],"cd")) {
                if(j>2) {
                    fprintf(stderr, "too many arguments\n");
                }
                else {
                    if(chdir(myargs[1])==-1) fprintf(stderr, "Error changing directory\n");
                }
            
                }*/ 
                else
                {
                    int rc = fork();
                    if(rc<0)
                    {
                        fprintf(stderr, "Fork failed\n");
                        exit(1);
                    }
                    else if(rc==0)
                    {
                        if(execvp(myargs[0], myargs)==-1) fprintf(stderr,"Command Execution Failed\n");
                    }
                    else
                    {
                        int wc = wait(NULL);
                    }
                }
            
            }
            //Freeing the allocated memory	
            //for(i=0;myargs[i]!=NULL;i++){
	          //  free(myargs[i]);
            //}
            free(myargs);
            
        }
    }
    return 0;
}
