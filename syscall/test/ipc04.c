#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 50

int main(int argc, char * argv[]){

	char msg[MAX];
	int fd;
	
	if((fd = open("./fifo", O_RDWR)) < 0){
		printf("Fail to open pipe\n");
		exit(1);
	}

	while(1){

		int nwrite = scanf("%s", msg);
		msg[MAX] = 0;
		if((write(fd, msg, MAX)) < 0){
			printf("Fail to write pipe\n");
			exit(1);
		}
		

//		if((read(fd, msg, MAX)) < 0){
//			printf("Fail to read pipe\n");
//			exit(1);
//		}	

//		printf("%s\n", msg);

	}


	return 0;


}
