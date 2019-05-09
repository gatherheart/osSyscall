#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


int main(){

	
	for(int i = 0; i < 3; i++){
		
		int pid = fork();
		if(pid == 0)
			printf("CHILD\n");

	}


	return 0;

}

/*
int main(){
	
	int pid, fd[2]; // child process and pipe

	if(pipe(fd) < 0){
		printf("Failed pipe creation\n");
	}
	
	if((pid = fork()) == 0){ // child Process
		close(fd[0]);
		dup2(fd[1], 1); 
		execlp("ps", "ps" , "a", "-o", "%cpu,%mem,cmd", NULL);	


	}	
	else{
		close(fd[1]);
		char buffer[MAX];
		while(1){
			int nread = read(fd[0], buffer, MAX);	
			if(nread <= 0)
				break;
			
			buffer[nread] = '\0';
			printf("%s", buffer);
		}
		for(int i = 0; i < 20; i++){
			printf("%s\n", "HELLOWORLD");
		}
		
		for(int i = 0; i < 20; i++){
			printf("\033[A\033[2K");
		}

		sleep(1);
		for(int i = 0; i < 20; i++){
			printf(ANSI_COLOR_RED "HelloWorld" ANSI_COLOR_RESET "\n");
		}


	}
	
}
*/
