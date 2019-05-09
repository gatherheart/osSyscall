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

	int n, cfd;
	struct hostent *h; // information of host(name, addtype...)
	struct sockaddr_in saddr;
	char buf[MAXLINE];
	char * host = argv[1];
	int port = atoi(argv[2]);

	if((cfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		printf("Socket failed.\n");
		exit(1);
	}

	if((h = gethostbyname(host)) == NULL){
		printf("Invalid hostname %s\n", host);
		exit(1);
	}

	memset((char *)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *)h->h_addr, (char *)&saddr.sin_addr.s_addr, h->h_length);
	saddr.sin_port = htons(port);


	while((n = read(0, buf, MAXLINE)) > 0){
		
		if(sendto(cfd, buf, n, 0, (struct socketaddr *)&saddr, sizeof(saddr)) < 0){
			printf("Send Error\n");
			exit(1);
		}
		memset(buf, 0, MAXLINE);	
		
		if(recvfrom(cfd, buf, MAXLINE, 0, (struct socketaddr *)&saddr, sizeof(saddr)) < 0){
			printf("recv Error\n");
			exit(1);
		}
		n = read(cfd, buf, MAXLINE);
		write(1, buf, n);
	}

	close(cfd);

}
