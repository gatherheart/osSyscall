#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define N 10

pid_t pid[N];
int ccount= 1;
void handler (int sig) {
	printf("\n");	
	for(int i = 0; i < 5; i++){
		printf("beep\n");
		sleep(1);
	}	
	ccount = 0;
}

int main(void) {
	int i;
	signal (SIGINT, handler);
	int pid;

	if((pid = fork()) == 0){
		exit(0);
	}
	else{	
		waitpid(pid, NULL ,0);
	}

	while(ccount){
	}		
	
	printf("I am alive\n");
	
	
	return 0;
}
