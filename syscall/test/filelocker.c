#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        int fd, ret;

        fd=open("locktest", O_RDWR | O_CREAT, 0644);
        ret=lockf(fd, F_LOCK, 0);
        printf("Locked By Pa: %d\n", ret);
        sleep(5);
	write(fd, "OK\n", 3);
	close(fd);
        printf("Released By Pa\n");

        return 0;
}
