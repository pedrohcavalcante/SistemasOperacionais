#define _GNU_SOURCE
#include <utmpx.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

void *runner(void *p){
	//while(1)
		printf("Esta é a execucao da Thread %d na CPU=%d\n", (int)(size_t) p, sched_getcpu());

	pthread_exit(NULL);
}
int main(int argc, char *argv[]){
	
	int i,j, NPROC, NTHREADS;
	NTHREADS=atoi(argv[1]);
	pthread_t tid[NTHREADS];
	pthread_attr_t attr_1, attr_2;
	cpu_set_t cpu_set_1, cpu_set_2;
	CPU_ZERO(&cpu_set_1);
    CPU_ZERO(&cpu_set_2);
    
	NPROC = sysconf(_SC_NPROCESSORS_ONLN);//OBTEM O NUMERO DE CORES DO SISTEMA
    printf ("Numero de Cores: %d\n", NPROC);
	for(i = 0;i < NPROC / 2; i++){
		CPU_SET(i, &cpu_set_1);//adiciona uma CPU ao conjunto
    }
    for (i = NPROC / 2; i < NPROC; i++){
        CPU_SET(i, &cpu_set_2);//adiciona uma CPU ao conjunto
    }

    pthread_attr_init(&attr_1);//inicializa a estrutura de atributos
    pthread_attr_init(&attr_2);//inicializa a estrutura de atributos
    
    pthread_attr_setaffinity_np(&attr_1, sizeof(cpu_set_t), &cpu_set_1);//estabelece a afinidade
    pthread_attr_setaffinity_np(&attr_2, sizeof(cpu_set_t), &cpu_set_2);//estabelece a afinidade

	for(i = 0;i < NTHREADS;i++)
        if (i % 2 == 0){
            pthread_create(&tid[i], &attr_1, runner, (void*)(size_t)i);
        }else{
            pthread_create(&tid[i], &attr_2, runner, (void*)(size_t)i);
        }


	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i], NULL);
	
    //sched_setaffinity(pid_t )


	pthread_attr_destroy(&attr_1);//destroy a estrutura de atributos
    pthread_attr_destroy(&attr_2);//destroy a estrutura de atributos

	return 0;
}