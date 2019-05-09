#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 80

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
		if ((connfd = accept(listenfd, (struct sockaddr *)&caddr, &caddrlen)) < 0){
			printf("Accecpt failed\n");
			continue;
		}
	
		h = gethostbyaddr((const char *)&caddr.sin_addr.s_addr, 
				sizeof(caddr.sin_addr.s_addr), AF_INET);
		printf("Server connected to %s (%s)\n", h->h_name, 
				inet_ntoa(*(struct in_addr *)&caddr.sin_addr));
		
		// echo
		while ((n = read(connfd, buf, MAXLINE)) > 0){
			printf("Got %d bytes from client. \n", n);
			write(connfd, buf, n);
			if(n == 2 && buf[0] =='\r' && buf[1] =='\n')
				puts("done");
		}
		
		printf("Connection terminated.\n");
		close(connfd);
	
	}

}
