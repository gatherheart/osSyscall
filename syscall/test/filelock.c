#include <stdio.h>;
#include <fcntl.h>;
#include <unistd.h>;

int main(int argc, char* argv[])
{
        int fd, ret;

        fd=open("locktest", O_RDWR);
        ret=lockf(fd, F_LOCK, 10L);
        printf("Locked By Pa: %d\n", ret);
        sleep(5);
        close(fd);
        printf("Released By Pa\n");

        return 0;
}
