#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

int sum;

void *summ(void *value){

	int upper = strtol(value, 0, 0);

	for(int i = 0; i <= upper; i++){
		sum += i;
	}
	

}

int main(int argc, char *argv[]){

	pthread_t tid;
	int thr_id;
	if(argc < 2){
		printf("Usage: %s number\n", argv[0]);
		exit(1);
	}

	thr_id = pthread_create(&tid, NULL, summ, argv[1]);
	pthread_join(tid, 0);
	printf("sum = %d\n", sum);
	
	return 0;
}
