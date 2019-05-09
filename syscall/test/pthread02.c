#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/types.h>

#define NTHREADS 4
#define MAXSBUF 10
#define MAXSIZE 80

typedef struct{
	int *buf;
	int n;
	int front;
	int rear;
	int count;
	pthread_mutex_t lock; //access control
	pthread_cond_t notfull;
	pthread_cond_t notempty;
} sbuf_t;

void sbuf_init(sbuf_t *sp, int n)
{
	pthread_mutex_init(&sp->lock, (pthread_mutexattr_t *)NULL);
        pthread_cond_init(&sp->notfull, (pthread_condattr_t *)NULL);
        pthread_cond_init(&sp->notempty, (pthread_condattr_t *)NULL);
        sp->n = n;
        sp->count = 0;
        sp->rear = 0;
        sp->front = 0;
        sp->buf = (int*)malloc(sizeof(int)*n);

};

void sbuf_delete(sbuf_t *sp)
{
	pthread_mutex_destroy(&sp->lock);
        pthread_cond_destroy(&sp->notfull);
        pthread_cond_destroy(&sp->notempty);
	free(sp->buf);
	return;
};

void *thread(void *vargp);

sbuf_t sbuf;

int main(int argc, char **argv)
{
	int i, listenfd, port;
	int connfd;
	socklen_t clientlen = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr, saddr;
	pthread_t tid;

	if(argc!=2)
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}

	port = atoi(argv[1]);
	sbuf_init(&sbuf, MAXSBUF);

	//socket creation
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		printf("socket() failed.\n");
		exit(1);
	}

	bzero((char *)&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);

	//bind
	if(bind(listenfd, (struct sockaddr *)&saddr,  sizeof(saddr))<0)
	{
		printf("bind() failed.\n");
		exit(2);
	}

	//listen
	if(listen(listenfd, 5)<0)
	{
		printf("listen() failed.\n");
		exit(3);
	}

	//pthread creation
	for(i=0; i<NTHREADS; i++)
		pthread_create(&tid, NULL, thread, NULL);

	while(1)
	{
		while(sbuf.count == MAXSBUF){
                        pthread_cond_wait(&sbuf.notfull, &sbuf.lock);
                }

		if((connfd  = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen))<0)
		{
			printf("accept() failed.\n");
			continue;
		}
		sbuf.buf[sbuf.rear] = connfd;
                sbuf.rear = (sbuf.rear + 1) % MAXSBUF;
                pthread_cond_signal(&sbuf.notempty);
		sbuf.count += 1;

	}

	//delete all
	sbuf_delete(&sbuf);



}

void *thread(void *vargp)
{

        char buf[MAXSIZE];
        int n = 0;
        while(1){
               
		pthread_mutex_lock(&sbuf.lock);
                while(sbuf.count == 0){
                        pthread_cond_wait(&sbuf.notempty, &sbuf.lock);
                }

		int connfd = sbuf.buf[sbuf.front];
                sbuf.front = (sbuf.front + 1) % MAXSBUF;
               	pthread_mutex_unlock(&sbuf.lock);
              	
	       	memset(buf, 0, sizeof(char)*MAXSBUF);	
		// echo
                while ((n = read(connfd, buf, MAXSIZE)) > 0){
	      		printf("tid %ld : %s",pthread_self(), buf);
                        write(connfd, buf, n);
                }

                printf("Connection terminated.\n");
                close(connfd);

                sbuf.count -= 1;
                pthread_cond_signal(&(sbuf.notfull));
        
	}


}
