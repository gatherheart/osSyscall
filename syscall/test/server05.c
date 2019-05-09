#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define MAXLINE 1024 

int which_type(char * buffer, int size){

        int i = 0;
        int ret = 1;
        int ret2 = 0;
        for(i = 0; i < size; i++){
                if(buffer[i] == '\"' || buffer[i] == '\'')
                        ret = 2;
                else if(buffer[i] == '*')
                        ret2 = 1;


                // convert to small letter
                if(buffer[i] >= 'A' && buffer[i] <= 'Z')
                        buffer[i] += 'a' - 'A';


        }
        return ret+ret2;

}

void send_file(int connfd, char * bible){

	int fd = open("out", O_RDONLY);
	int nread = 0;
	char buffer[MAXLINE+1];
	memset(buffer, 0, MAXLINE);
	while((nread = read(fd, buffer, MAXLINE)) > 0){
		buffer[nread] = '\0';
		puts(buffer);
		write(connfd, buffer, nread);
	}
	write(connfd, '\0', 1);
	close(fd);
	return;

}

int main(int argc, char *argv[]){

	int n, listenfd, connfd, caddrlen;
	struct hostent *h; // information of host(name, addtype...)
	struct sockaddr_in saddr, caddr;
	char buf[MAXLINE];
	int port = atoi(argv[1]);

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Socket failed.\n");
		exit(1);
	}

	memset((char *)&saddr, 0,  sizeof(saddr));

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);
	
	if(bind(listenfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
		printf("Bind failed.\n");
		exit(1);
	}
	if(listen(listenfd, 5) < 0){
		printf("listen failed.\n");
		exit(1);
	}


	while(1){
		caddrlen = sizeof(caddr);
		if ((connfd = accept(listenfd, (struct sockaddr *)&caddr, (socklen_t *)&caddrlen)) < 0){
			printf("Accecpt failed\n");
			continue;
		}
	
		h = gethostbyaddr((const char *)&caddr.sin_addr.s_addr, 
				sizeof(caddr.sin_addr.s_addr), AF_INET);
		printf("Server connected to %s (%s)\n", h->h_name, 
				inet_ntoa(*(struct in_addr *)&caddr.sin_addr));
		
		// echo
		while ((n = read(connfd, buf, MAXLINE)) > 0){
			buf[n] = '\0';
			
			int type = which_type(buf, n);

			printf("type:%d Got %d bytes from client. \n", type, n);
			
			if(type == 1){
				send_file(connfd, "test");
			}
			else{
				write(connfd, buf, n);
				write(connfd, '\0', 1);
			}
		}
		
		printf("Connection terminated.\n");
		close(connfd);
	
	}

}


