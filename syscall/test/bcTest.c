#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>

int main(){
	
	
	execlp("echo", "echo", "1+2", 3, NULL);
	execlp("bc", "bc", NULL);

}
