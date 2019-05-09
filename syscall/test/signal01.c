#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define N 10

int main(void)
{	 
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);

	pid_t pid[N];
	int i, child_status;

	for (i = 0; i < N; i++) {
		if ((pid[i] = fork()) == 0) {
			while(1); /* Child infinite loop */
		}
	}	
	

	for (i = 0; i < N; i++){
		kill(pid[i], SIGINT);
	}


	/* Parent terminates the child processes (Your C code)*/
	/* Parent reaps terminated children */
		
		
	
	for (i = 0; i < N; i++) {
	pid_t wpid= wait(&child_status);
	if (WIFEXITED(child_status))
		printf("Child %d terminated with exit status %d\n",
		wpid, WEXITSTATUS(child_status));
	else
		printf("Child %d terminated abnormally\n", wpid);
	}
	return 0;

}
