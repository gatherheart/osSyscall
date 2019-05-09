#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int args, char *argv[]){

	int pd[2];
	if(args != 5)
		exit(1);
	if(pipe(pd) < 0)
	       	exit(1);

	if(fork() == 0){
		close(pd[0]);
	
		dup2(pd[1], 1);
		execlp(argv[1], argv[1], argv[2], NULL);
	}
	else{
		close(pd[1]);
		dup2(pd[0], 0);
		execlp(argv[4], argv[4], NULL);	
	}

	exit(0);





}
