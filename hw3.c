#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

// displays message of a catching CTR^C signal 
void sigint_handler(int sig){
	  char msg1[] = "caught sigint\nCS361 >";
	    write(1, msg1, sizeof(msg1));
}

// diplays message of catching CTR^Z signal
void sigtstp_handler(int sig){
	char msg[]="caught sigtstp\nCS361 >";
	write(1,msg,sizeof(msg));
}

//for regular commands like /bin/ls -l
//executes them
void regArg(char **argsArray){
	int pid = fork();
	int status;
	if(pid == 0){
		execv(argsArray[0],argsArray);
	}else{
		wait(&status);
		printf("pid:%d status:%d\n",pid, WEXITSTATUS(status));
	}
}

//Piping commands like /bin/ls | grep hw
//and executing them
void pipeArg(char **first, char **second){

	int piped[2];
	pid_t pid1,pid2;
	pipe(piped);
	int status;
	pid1 = fork();
	if(pid1 == 0){
		//close(piped[0]);
		dup2(piped[1],STDOUT_FILENO);///has value of 1
		close(piped[0]);
		close(piped[1]);
		execvp(first[0],first);
		exit(1);
	}else{
		//wait(&status);
		pid2 = fork();
		if(pid2==0){
		//	close(piped[1]);
			dup2(piped[0],STDIN_FILENO);// has value of 0
			close(piped[1]);
			close(piped[0]);
			execvp(second[0],second);
			exit(1);
		}else{
			close(piped[0]);
			close(piped[1]);
			wait(&status);
		}
		wait(&status);
		printf("pid:%d status:%d\n",pid1,WEXITSTATUS(status));
		printf("pid:%d status:%d\n",pid2,WEXITSTATUS(status));
	}
}

int main(){
	
	  signal(SIGINT, sigint_handler);
	  signal(SIGTSTP,sigtstp_handler);

	while(1){
	TSTATUS(status)char **argsarray printf("CS31 >");
	char line[500];
	int x= 0;
	char **argsarray = (char**)malloc(100*sizeof(char*));
	char **argsarray2 = (char**)malloc(100*sizeof(char*));
	for(int i = 0; i <= 100;i++ )
	{
		argsarray[i]=(char*)malloc(20*sizeof(char));
		argsarray2[i]=(char*)malloc(20*sizeof(char));
	}
	fgets(line, 500, stdin);
	char *word;
	if(line[0]=='e' && line[1]=='x' && line[2]=='i'&& line[3]=='t'){
		exit(EXIT_SUCCESS);
	}
	
	for(int i =0; i < 500;i++){
		if(line[i]=='\n'){
			line[i]='\0';
			break;
		}
	}
	char** tmp2 =(char**)malloc(100*sizeof(char*));
	for(int i = 0; i <= 100;i++){
		tmp2[i]=(char*)malloc(20*sizeof(char));
	}
	if(strchr(line,';')!=0){
		char* tmp= strtok(line,";");//<--------tokenize for ;
		 int c = 0;
		 int d = 0;
		 int e = 0;
		 while(tmp){// After tokenizing, I put in to tmp array
			strcpy(tmp2[c],tmp);
			tmp=strtok(NULL, ";");
			c++;
		 }
		char* first = strtok(tmp2[0]," ");//tmp2[0] should tokenize/bin/ls -l
		//argsarray is a double char**. first holds the tokenized /bin/ls -l
		while(first){
			strcpy(argsarray[d],first);
			first = strtok(NULL," ");
			d++;
		}
		char* second = strtok(tmp2[1]," ");
		//argsarray2 is another double char** and holds /bin/ps -e 
		while(second){
			strcpy(argsarray2[e],second);
			second = strtok(NULL," ");
			e++;
		}
		//make endings null
		argsarray[d]=(char*)0;
		argsarray2[e]=(char*)0;
		
		//BUT prints wrong thing.whyyyyyy????
		regArg(argsarray);
		regArg(argsarray2);	
		
	}else if(strchr(line,'|')!=0){
		char* tmp= strtok(line,"|");//<--------tokenize for ;
		int c;
		int d;
		int e;
		while(tmp){
			strcpy(tmp2[c],tmp);
			tmp=strtok(NULL,"|");
			c++;
		}
		char *first = strtok(tmp2[0]," ");
		while(first){
			strcpy(argsarray[d],first);
			 first = strtok(NULL," ");
			 d++;
		}
		char* second = strtok(tmp2[1]," ");
		while(second){
			strcpy(argsarray2[e],second);
			second = strtok(NULL," ");
			e++;
		}
		argsarray[d]=(char*)0;
		argsarray2[e]=(char*)0;
		pipeArg(argsarray,argsarray2);
	}
	else{
		word = strtok(line, " ");
 		while(word){
			strcpy(argsarray[x],word);
			word = strtok(NULL," ");
                	x++;
		}
	        argsarray[x]=(char *)0;
	regArg(argsarray);
	}
ar **argsarray }
	return 0;
}


