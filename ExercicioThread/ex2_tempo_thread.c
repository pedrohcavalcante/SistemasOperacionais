#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* hello_world(void *tid){
	printf("Hello World. Esta é a Thread %d\n", (int)tid);
	//sleep(((int)tid+1)*2);
	pthread_exit(NULL);
}

int main(){
	int i, status;
	struct timeval tempo1, tempo2;
	pthread_t thread_id;
	
	
	gettimeofday(&tempo1, NULL);
	status = pthread_create(&thread_id, NULL, hello_world, (void*)(size_t)1);
	gettimeofday(&tempo2, NULL);
	printf("tempo de criação de uma thread: %ld microssegundos\n", ((tempo2.tv_sec * 1000000 + tempo2.tv_usec) - (tempo1.tv_sec * 1000000 + tempo1.tv_usec)));
	return 0;
}
