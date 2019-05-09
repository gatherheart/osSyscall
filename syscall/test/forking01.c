#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void fork1(){

	int x = 1;
	pid_t pid = fork(); 
	// child process will start from here
	if(pid == 0)
		printf("Child has x = %d\n", ++x);
	else
		printf("Parent has x = %d\n", --x);

	printf("Bye from process %d with x = %d\n", getpid(), x);
	printf("%d\n", WNOHANG);
}

int main(){


	fork1();


}
