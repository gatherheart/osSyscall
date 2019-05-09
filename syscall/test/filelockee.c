#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        int fd, ret;

        fd=open("locktest", O_RDWR);
       	
	while((ret = lockf(fd, F_TEST, 0)) == -1)
		printf("PENDING\n"); 
	char buffer[100];
	read(fd, buffer, 100);
	puts(buffer);
	close(fd);
        printf("Released By Pb\n");

        return 0;
}
