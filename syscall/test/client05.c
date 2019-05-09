#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 1024 

void read_file(int cfd, char buffer[MAXLINE], MAXLINE){
	
	while((nread = read(cfd, buffer, MAXLINE)) > 0){
		write(1, buffer, nread);
		if(nread != MAXLINE || buffer[nread] == '\0')
			break;
	}
	return;
}

int main(int argc, char *argv[]){

	int n, cfd;
	struct hostent *h; // information of host(name, addtype...)
	struct sockaddr_in saddr;
	int bible_num = 0;
	char buf[MAXLINE];
	char * host = argv[1];
	int port = atoi(argv[2]);

	if((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
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

	if(connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
		printf("connection failed.\n");
		exit(1);
	}
	
	n = read(cfd, buf, MAXLINE);
	
	if(n < 1){
		printf("connection error, please retry\n");
		exit(1);
	}
	
	int bible_num = atoi(buf);

	while((n = read(0, buf, MAXLINE)) > 0){
		write(cfd, buf, n);
		int nread = 0;
		char buffer[MAXLINE + 1];
		memset(buffer, 0, MAXLINE);
		for(int i = 0; i < bible_num; i++)
			read_file(cfd, buffer, MAXLINE);	
	}
			
	close(cfd);

}
