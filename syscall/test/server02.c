#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 80
#define MAX 100

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
			int pipefd[2] = {0, };

			int pid, fd[2]; // child process and pipe

			if(pipe(pipefd) < 0){
				printf("Failed pipe creation\n");
			}
			
			if((pid = fork()) == 0){ // child Process
				dup2(pipefd[0], 0);
				dup2(pipefd[1], 1); 
				int pd[2];
				if(pipe(pd) < 0) exit(1);

				if(fork() == 0){
					close(pd[0]);
					dup2(pd[1], 1);
					execlp("echo", "echo", buf, NULL);
				}
				else{
					dup2(pipefd[1], 1); 
					dup2(pd[0], 0);
					char buffer[100];
					execlp("bc", "bc", NULL);
				}

				exit(0);
					
			}	

			char buffer[MAX];
			
			while(1){
				int nread = read(pipefd[1], buffer, MAX);
				if(nread <= 0)
					break;

				buffer[nread] = '\0';
				printf("%s", buffer);
			}

			
			write(connfd, buf, n);
	
		}
		
		printf("Connection terminated.\n");
		close(connfd);
	
	}

}
