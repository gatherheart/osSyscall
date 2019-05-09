#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>


void *thread_function(void *t_name){

	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	char * thread_name = (char*)t_name;
	int i = 0;

	while(i < 3){
		printf("[%s] pid:%u tid:%lx\n", (char*)t_name, pid, tid);
		i += 1;
	}

	return (void *)1;
}

int main(int argc, char *argv[]){

	pthread_t tid[2];
	int thr_id;
	int status;
	char p_1[] = "thread_1";
	char p_2[] = "thread_2";
	char p_3[] = "thread_m";

	sleep(1);
	thr_id = pthread_create(&tid[0], NULL, (void *)thread_function, (void*)p_1);
	
	if(thr_id < 0){
		return 0;
	}

	thr_id = pthread_create(&tid[1], NULL, (void *)thread_function, (void*)p_2);
	
	if(thr_id < 0){
		return 0;
	}

	thread_function((void *)p_3);	
	for(int i = 0; i < 2; i++)
		pthread_join(tid[i], 0);
	
	return 0;
}
