#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){


	int pd[2];
	if(pipe(pd) < 0) exit(1);

	if(fork() == 0){
		close(pd[0]);
		dup2(pd[1], 1);
		execlp("echo", "echo", "124 * (42 + 3) % 17", NULL);
	
	}
	else{
		close(pd[1]);
		dup2(pd[0], 0);
		char buffer[100];
		
		execlp("bc", "bc", NULL);	
	}

	exit(0);





}
