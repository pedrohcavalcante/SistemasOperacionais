#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

void *runner(void *p){
	int r;
	cpu_set_t cpu_set;//cria uma variavel do tipo cpu_set_t
        CPU_ZERO(&cpu_set); //inicializa a variavel sem informacao

        CPU_SET(3, &cpu_set);//adiciona uma cpu na lista
        CPU_SET(2, &cpu_set);

	r = sched_setaffinity(0, sizeof(cpu_set_t), &cpu_set);	//estabelece a afinidade
        
	while(1)
	        printf("Esta é a execucao da Thread %d na CPU=%d; afinidade=%d\n", (int)(size_t) p, sched_getcpu(), r);

        pthread_exit(NULL);
}
int main(int argc, char *argv[]){
    
        int i, scope, r, NTHREADS;
	
	NTHREADS = atoi(argv[1]);
        
	pthread_t tid[NTHREADS];
        pthread_attr_t attr;
	pthread_attr_init(&attr);//inicializa a estrutura de atributos
        
	for(i=0;i<NTHREADS;i++)
                pthread_create(&tid[i], &attr, runner, (void*)(size_t)i);

        for(i=0;i<NTHREADS;i++)
                pthread_join(tid[i], NULL);

	pthread_attr_destroy(&attr);//destroi a estrutura de atributos

        return 0;
}

