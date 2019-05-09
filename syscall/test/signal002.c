#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define N 10

pid_t pid[N];
int ccount= 0;
void handler (int sig) {
	int child_status;
	pid_t id = wait(&child_status);
	int ret = WEXITSTATUS(child_status);
	ccount--;
	printf("Received signal %d from pid%d\n", sig, id);

	kill(pid[ret], SIGINT);
}

int main(void) {
	int i;
	ccount= N;
	signal (SIGCHLD, handler);
	for (i = 0; i < N; i++) {
		if ((pid[i] = fork()) == 0) {
		exit(i); /* child */
		}
	}
	while (ccount> 0)
		sleep (5);
	return 0;
}
