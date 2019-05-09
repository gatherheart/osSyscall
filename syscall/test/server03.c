#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
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
			printf("%s\n", buf);

			char buffer[MAXLINE];
			int lhs = 0;
			int rhs = 0;
			char op = 0;
			int result = 0;
			
			sscanf(buf, "%d%c%d", &lhs, &op, &rhs);


			if( (lhs < '0' && lhs > '9') || (rhs < '0' && lhs > '9')){
				write(connfd, "ERROR\n", 6);
				continue;	
			}
			if(op != '+' && op != '-' && op != '*' && op != '%' && op != '/'){
				write(connfd, "ERROR\n", 6);
				continue;
			}
			
			switch(op){
				case '+':
					result = lhs + rhs;
					break;
				
				case '-':
					result = lhs - rhs;
					break;
				
				case '*':
					result = lhs * rhs;
					break;

				case '/':
					result = lhs / rhs;
					break;

				case '%':
					result = lhs % rhs;
					break;
				
				default:
					break;
			}
			printf("%d\n", result);
			int t = sprintf(buffer, "result : %d\n", result);
			printf("%d\n", t);
			write(connfd, buffer, t);



		}
		
		printf("Connection terminated.\n");
		close(connfd);
	
	}

}
