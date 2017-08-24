#define _GNU_SOURCE
#include <utmpx.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

void *runner(void *p){
	while(1)
		printf("Esta é a execucao da Thread %d na CPU=%d\n", (int)(size_t) p, sched_getcpu());

	pthread_exit(NULL);
}
int main(int argc, char *argv[]){
	
	int i, NPROC, NTHREADS;
	NTHREADS=atoi(argv[1]);
	pthread_t tid[NTHREADS];
	pthread_attr_t attr;
	cpu_set_t cpu_set;
	CPU_ZERO(&cpu_set);

	NPROC = sysconf(_SC_NPROCESSORS_ONLN);//OBTEM O NUMERO DE CORES DO SISTEMA

	//for(i=0;i<4;i++)
		CPU_SET(0, &cpu_set);//adiciona uma CPU ao conjuntp
		CPU_SET(1, &cpu_set);

	pthread_attr_init(&attr);//inicializa a estrutura de atributos
	pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_set);//estabelece a afinidade

	for(i=0;i<NTHREADS;i++)
		pthread_create(&tid[i], &attr, runner, (void*)(size_t)i);

	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i], NULL);
	
	pthread_attr_destroy(&attr);//destroy a estrutura de atributos

	return 0;
}
