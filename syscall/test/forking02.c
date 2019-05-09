#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int rat(int n){

	pid_t pid,child;
	int status;
	int rat1=0, rat2=0;

 
	if(n <= 1) 
		return(1);

 
	if((pid = fork()) < 0)
		exit(1);

	else if(pid==0){        
		rat1 = rat(n-1);
		exit(rat1); 
	}
	else{ 
	
		child=wait(&status);
		
	//	printf("%d  ", status);
		rat1 = WEXITSTATUS(status);   
		printf("%d \n", rat1);
		rat2 = rat(n-2);        
	
		
//	printf("These rabbits are %d-month old\n", n-2);

}

return (rat1+rat2);

}

 

int main(){

 
	int n;

	scanf("%d", &n);

	int result = rat(n);


	return 0;

}
