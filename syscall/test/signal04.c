#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int main(void)
{
	sigset_t sigset;
	int ndx;
	sigemptyset(&sigset);
	sigaddset(&sigset,SIGINT);
	
	//Block Mode
	
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	
	//Start counting
	
	for(ndx= 3; 0 < ndx; ndx--){
		printf("Count Down: %d\n",ndx);
		sleep(1);
	}
	
	//Unblock Mode
	
	printf("Unblock");
	sigprocmask(SIG_UNBLOCK,&sigset,NULL);
	printf("If you press CTRL-C, This sentence is not printed\n");
	
	while(1);
	return 0;
}
