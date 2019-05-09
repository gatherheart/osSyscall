#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

int main(){
	
	char msg[MAX];
	int fd;
	int nread, cnt;

	if(mkfifo("./fifo", 0666) < 0){
		printf("Fail to make pipe\n");
		exit(1);
	}

	if((fd = open("./fifo", O_RDWR)) < 0){
		printf("Fail to open pipe\n");
		exit(1);
	}

	while(1){
		if((nread = read(fd, msg, MAX)) < 0){
			printf("Fail to read pipe\n");
			exit(1);
		}
		msg[nread] = '\0';
		printf("Received: %s\n", msg);
	//	write(fd, msg, nread);
	}
	
	unlink("./fifo");
	return 0;

}
