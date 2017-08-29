#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int *vetA;
int aux;

void *runner(void *p){
		//printf("Esta é a execucao da Thread %d\n", (int)(size_t) p);
        int mult = vetA[(int)(size_t)p * 2] * vetA[(int)(size_t)p*2 +1];
        printf(">> Eu sou a thread %d e o resultado da multiplicação é %d\n", (int)(size_t) p, mult );
        //printf(">>>VetA =  %d || vetA %d <<< \n", vetA[(int)(size_t)p * 2], vetA[(int)(size_t)p*2 +1]);

    //printf("Esta é a execucao da Thread %d\n", (int)(size_t) p);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    
    int NTHREADS = atoi(argv[1]);
    int i, scope, r;
	pthread_t tid[NTHREADS];
	pthread_attr_t attr;

    vetA = malloc(NTHREADS * sizeof(int));

    srand(time(NULL));//inicializa a semente (só deve ser feito UMA vez)
	for(i = 0;i < NTHREADS; i++){
		vetA[i] = rand()%100; //garante que o número está entre 0 e 99
		printf("Valor %d inserido na posicao %d do vetor A\n", vetA[i], i);
	}

    pthread_attr_init(&attr);
    r = pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);

    for (aux = 0; aux < NTHREADS / 2; aux++){
        pthread_create(&tid[aux], &attr, runner, (void*)(size_t)aux);
    }

    pthread_attr_destroy(&attr);

    free(vetA);
}