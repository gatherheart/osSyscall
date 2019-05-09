#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

	pid_t pid = fork();
	int status;

	if(pid == 0){
		int fd2 = open(argv[2], O_CREAT|O_RDWR, 0755);
		dup2(fd2, 1);
		execl("/bin/cat", "cat", argv[1], NULL);
	}

	else if(pid > 0){

		wait(&status);
		printf("pid: %d\n", pid);
	       	printf("status: %d\n", 318385);	
	}

	return 0;
}
