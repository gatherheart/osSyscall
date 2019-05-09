#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define N 10

pid_t pid[N];
int ccount= 0;

void handler (int sig) {
	
	pid_t id ;
//	ccount--;

       for(int i = 0; i < N; i++){
		//id = waitpid(pid[i], NULL, WNOHANG);	
	       id = wait(NULL);	
	       if(id > 0)
		{	
			ccount--;
			printf("Received signal %d from pid %d\n", sig, id);	
		}
		
	}		

}

int main(void) {
	int i;
	ccount= N;
	int status;
	signal (SIGCHLD, handler);
	for (i = 0; i < N; i++) {
		if ((pid[i] = fork()) == 0) {
			printf("%d\n", pid[i]);

			exit(0); /* child */
		}

	}
	while (ccount> 0)
		sleep (5);
	return 0;
}

