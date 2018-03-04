//Harkirat Rakhra 0969501

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

extern char **getln();

int main(void) {
	int i =0;
	int j=0;
	char buffer[300];
	char **args;
	pid_t pid;
	char argument[200];
	int argCounter =0;
	int argInteger =0;
	long addArg=0;
	long picNum=0;
	
	while(1) {
	  i =0;
	  
	  getcwd(buffer,sizeof(buffer));
	  printf("%s:>>",buffer);
	  args = getln();

	  if(args[0] == NULL){
	    printf("No input Detected\n");
	    continue;
	  }

	  else if(strcmp(args[0],"arg") == 0){
	    argCounter=0;
	    printf("Args:");
	    while(args[i] != NULL){
	      if(args[i +1] != NULL){
		strcpy(argument,args[i + 1]);
		printf("%s ",argument);
		argCounter++;
	      }
	      i++;
	    }
	    printf("argc: %d\n",argCounter);
	  }

	   else if(strcmp(args[0],"pics") == 0){
	    if(args[1] == NULL){
	      printf("\t\t ^ ^\n");
	      printf("\t\t(o,o)\n");
	      printf("\t\t(   )\n");
	      printf("\t\t v v\n");
	    }
	    else{
	      picNum = strtol(args[1],NULL,10);
	      for(j=0; j < picNum; j++){
		 printf("\t\t ^ ^\n");
		 printf("\t\t(o,o)\n");
		 printf("\t\t(   )\n");
		 printf("\t\t v v\n");
	      }
	    }
	    
	  }

	  else if(strcmp(args[0],"add") == 0){
	    addArg=0;
	    if(args[i + 1] == NULL ){
	      printf("Need more arguments\n");
	    }

	    do{
	      argInteger = 0;
	      argCounter =0;

	      if(args[i + 1] != NULL){
		strcpy(argument,args[i +1]);
		//has to be strtol 0 for hex values
		argInteger = strtol(argument,NULL,0);

	        addArg += argInteger;
		argCounter ++;
		i++;
	      }
	    }while(args[i + 1] != NULL);
        
	    printf("%ld\n",addArg);
	    
	  }
	  
	  else if(strcmp(args[0],"exit") == 0){
	    exit(0);
	  }

	  else if(args[1] == NULL){
	    pid = fork();

	    if(pid == 0){
	      execvp(args[0],args);
	      exit(0);
	    }
	    else if(pid < 0){
	      printf("Fork Error\n");
	      exit(0);
	    }
	   
	    else{
	      wait(NULL);
	    }
	  }
	  
	  else if(args[1] != NULL){
	    do{
	      if(strcmp(">",args[i + 1]) ==0){
		// + 2 because filename should  be 1 away from the >
		freopen(args[i + 2], "w",stdout);
	      }
	      else if(strcmp("<",args[i + 1]) == 0){
		freopen(args[i + 2], "r",stdin);
	      }
	      i++;
	    }while(args[i + 1] != NULL);
	    pid = fork();

	    if(pid < 0){
	      printf("Fork Error:");
	    }
	    else if(pid == 0){
	      execvp(args[0],args);
	      exit(0);
	    }
	    else{
	      wait(NULL);
	    }
	  }

	  else{
	    printf("Unknown Command\n");
	  }
	}
	
	return(0);
}

