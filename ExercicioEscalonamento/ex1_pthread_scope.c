#include <pthread.h>
#include <stdio.h>
#define NTHREADS 5

void *runner(void *p){
	//while(1)
		printf("Esta é a execucao da Thread %d\n", (int)(size_t) p);

	pthread_exit(NULL);
}
	

int main(int argc, char *argv[]){
	
	int i, scope, r;
	pthread_t tid[NTHREADS];
	pthread_attr_t attr;

	pthread_attr_init(&attr);//inicializa a estrutura de atributos
	r = pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);//estabelece o escopo
	if(pthread_attr_getscope(&attr, &scope) != 0)
		printf("Nao foi possivel obter o escopo do escalonamento\n");
	else{
		if(scope==PTHREAD_SCOPE_PROCESS)
			printf("PTHREAD_SCOPE_PROCESS\n");
		else if(scope==PTHREAD_SCOPE_SYSTEM)
			printf("PTHREAD_SCOPE_SYSTEM\n");
		else
			printf("Valor de escopo ilegal\n");
	}
	
	for(i=0;i<NTHREADS;i++)
		pthread_create(&tid[i], &attr, runner, (void*)(size_t)i);

	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i], NULL);
	
	pthread_attr_destroy(&attr);//destroi a estrutura de atributos

	return 0;
}
