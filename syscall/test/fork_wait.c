#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(){

	pid_t pid = fork();
	int child_status;
	if(pid > 0){
		printf("%d CHILD START\n", pid);
		int t = wait(&child_status);
		printf("%d %d,  PARENT DONE\n",t, child_status);
	}

	else if(pid == 0){	
		sleep(5);	
		printf("CHILD DONE\n");
		exit(1);
	}

}

