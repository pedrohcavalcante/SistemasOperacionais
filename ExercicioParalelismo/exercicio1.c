#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define NumLinhas 100
#define NumColunas 10
#define NumThreads 10

pthread_mutex_t mutex;
int matriz[NumLinhas][NumColunas];


void printMatrix(){
    int cont, cont2;
    for (cont = 0; cont < NumLinhas; cont++){
        for (cont2 = 0; cont2 < NumColunas; cont2++){
            printf("Matrix[%d][%d]=%d", cont, cont2, matriz[cont][cont2]);
        }
        printf("\n");
    }
}

void inicializa_matriz(){
    int i, j, n;
	for(j = 0;j < NumLinhas; j++)
        for (i = 0; i < NumColunas; i++){
            matriz[j][i] = rand()%100;
        }
}

void* soma(void *p){
    int i, soma=0;
    pthread_mutex_lock(&mutex);	
        for (i = 0; i < NumLinhas; i++){
            soma += matriz[i][(int)(size_t)p];
        }
    pthread_mutex_unlock(&mutex);
    printf("Thread %d somou %d\n", (int)(size_t)p, soma);

}

int main(){
    int i;
    pthread_t tid[NumThreads];

    pthread_mutex_init(&mutex, NULL);

    srand(time(NULL));

    inicializa_matriz();

    //Criar Threads 
    for (i = 0; i < NumThreads; i++){
        pthread_create(&tid[i], NULL, soma, (void *)(size_t) i);
    }

    for (i = 0; i < NumThreads; i++){
        pthread_join(tid[i], NULL);
    }

    //printMatrix();
    pthread_mutex_destroy(&mutex);	

}
