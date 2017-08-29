#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int *vetA;
int *vetB; 
int aux;

void *runner(void *p){
		//printf("Esta é a execucao da Thread %d\n", (int)(size_t) p);
        int soma = vetA[(int)(size_t)p] + vetB[(int)(size_t)p];
        printf(">> Eu sou a thread %d e o resultado da soma é %d\n", (int)(size_t) p, soma );
        //printf(">>>VetA =  %d || vetB %d <<< \n", vetA[(int)(size_t)p], vetB[(int)(size_t)p]);

	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    
    int NTHREADS = atoi(argv[1]);
    int i, scope, r;
	pthread_t tid[NTHREADS];
	pthread_attr_t attr;

    vetA = malloc(NTHREADS * sizeof(int));
    vetB = malloc(NTHREADS * sizeof(int));

    srand(time(NULL));//inicializa a semente (só deve ser feito UMA vez)
	for(i = 0;i < NTHREADS; i++){
		vetA[i] = rand()%100; //garante que o número está entre 0 e 99
		printf("Valor %d inserido na posicao %d do vetor A\n", vetA[i], i);
	}

	for(i = 0;i < NTHREADS; i++){
		vetB[i] = rand()%100; //garante que o número está entre 0 e 99
		printf("Valor %d inserido na posicao %d do vetor B\n", vetB[i], i);
	}


    pthread_attr_init(&attr);
    r = pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);

    for (aux = 0; aux < NTHREADS; aux++){
        pthread_create(&tid[aux], &attr, runner, (void*)(size_t)aux);
    }

    pthread_attr_destroy(&attr);

    free(vetA);
    free(vetB);
}