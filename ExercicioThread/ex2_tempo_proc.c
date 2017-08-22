#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int i;
	struct timeval tempo1, tempo2;
	pid_t pid;	
	
	gettimeofday(&tempo1, NULL);
	pid = fork();
	gettimeofday(&tempo2, NULL);
	if(pid){
		printf("tempo de criação de um processo: %ld microssegundos\n", ((tempo2.tv_sec * 1000000 + tempo2.tv_usec) - (tempo1.tv_sec * 1000000 + tempo1.tv_usec)));
	}
	return 0;
}
