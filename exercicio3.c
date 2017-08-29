#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <utmpx.h>
#include <unistd.h>
#include <sched.h>

int *vetA;
int aux;

void *runner(void *p){
		//printf("Esta é a execucao da Thread %d\n", (int)(size_t) p);
        int mult = vetA[(int)(size_t)p * 2] * vetA[(int)(size_t)p*2 +1];
        printf(">> Eu sou a thread %d e o resultado da multiplicação é %d na CPU %d\n", (int)(size_t) p, mult, sched_getcpu() );
        //printf(">>>VetA =  %d || vetA %d <<< \n", vetA[(int)(size_t)p * 2], vetA[(int)(size_t)p*2 +1]);

    //printf("Esta é a execucao da Thread %d\n", (int)(size_t) p);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    
    int NTHREADS = atoi(argv[1]);
    int i, scope, r, NPROC;
	pthread_t tid[NTHREADS];
	

    vetA = malloc(NTHREADS * sizeof(int));
    NPROC = sysconf(_SC_NPROCESSORS_ONLN);
    cpu_set_t cpu_set[NPROC];
    CPU_ZERO(&cpu_set[NPROC]);
    pthread_attr_t attr[NPROC];


    printf(">>> Números de Processadores Disponíveis: %d\n", NPROC);
    srand(time(NULL));//inicializa a semente (só deve ser feito UMA vez)
	for(i = 0;i < NTHREADS; i++){
		vetA[i] = rand()%100; //garante que o número está entre 0 e 99
		printf("Valor %d inserido na posicao %d do vetor A\n", vetA[i], i);
	}

    
    //r = pthread_attr_setscope(&attr[NPROC], PTHREAD_SCOPE_PROCESS);

    for(i = 0;i < NPROC; i++){
        CPU_SET(i, &cpu_set[i]);
        pthread_attr_init(&attr[i]);
        pthread_attr_setaffinity_np(&attr[i], sizeof(cpu_set_t), &cpu_set[i]);//estabelece a afinidade
    }

    for (aux = 0; aux < NTHREADS; aux++){
        if (aux % NPROC == 0){
            pthread_create(&tid[aux], &attr[aux], runner, (void*)(size_t)aux);
        }else if (aux % NPROC == 1){
            pthread_create(&tid[aux], &attr[aux], runner, (void*)(size_t)aux);
        }else if(aux % NPROC == 2){
            pthread_create(&tid[aux], &attr[aux], runner, (void*)(size_t)aux);
        }else if (aux % NPROC == 3){
            pthread_create(&tid[aux], &attr[aux], runner, (void*)(size_t)aux);
        }
    }

    for (i = 0; i < NPROC; i++){
        pthread_attr_destroy(&attr[i]);
    } 

    free(vetA);
}