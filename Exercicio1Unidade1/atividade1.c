#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
int somaprod, szMatrix;
int **matrizA;
int **matrizB;
int **matrizC;

void inicializa_matriz_A(){
    int i, j, n;
	for(j = 0;j < szMatrix; j++)
        for (i = 0; i < szMatrix; i++){
            matrizA[j][i] = 1;
        }
}

void inicializa_matriz_B(){
    int i, j, n;
	for(j = 0;j < szMatrix; j++)
        for (i = 0; i < szMatrix; i++){
            matrizB[j][i] = 2;
        }
}

void printMatrix(){
    int cont, cont2;
    for (cont = 0; cont < szMatrix; cont++){
        for (cont2 = 0; cont2 < szMatrix; cont2++){
            printf("[%d]", matrizA[cont][cont2]);
        }
        printf("\n");
    }
    for (cont = 0; cont < szMatrix; cont++){
        for (cont2 = 0; cont2 < szMatrix; cont2++){
            printf("[%d]", matrizB[cont][cont2]);
        }
        printf("\n");
    }
    for (cont = 0; cont < szMatrix; cont++){
        for (cont2 = 0; cont2 < szMatrix; cont2++){
            printf("[%d]", matrizC[cont][cont2]);
        }
        printf("\n");
    }
}

void* multiplica(void *p){
    int linha = (int)(size_t)p;
    int coluna, i, soma;
    pthread_mutex_lock(&mutex);	
    //for (linha = 0; linha < szMatrix; linha++){
        for (coluna = 0; coluna < szMatrix; coluna++){
            soma = 0;
            for (i = 0; i < szMatrix; i++){
                //printf("calculando elemento MatrizA[%d][%d] * MatrizB[%d][%d]\n", linha, i, i, coluna);
                soma += matrizA[linha][i] * matrizB[i][coluna];
                //printf("calculando elemento MatrizA[%d][%d] * MatrizB[%d][%d] = %d\n", linha, i, i, coluna, soma);
               
            }
             matrizC[linha][coluna] = soma;
        }
    //}
     pthread_mutex_unlock(&mutex);
}
int main(int argc, char **argv) {
    szMatrix = atoi(argv[1]);
    pthread_t tid[szMatrix];
    int i;

    pthread_mutex_init(&mutex, NULL);
    // ALOCAÇÃO DAS MATRIZES
    matrizA = (int **)malloc(sizeof(int*)*szMatrix);
    matrizB = (int **)malloc(sizeof(int*)*szMatrix);
    matrizC = (int **)malloc(sizeof(int*)*szMatrix);
    // ALOCAÇÃO DAS COLUNAS DAS MATRIZES
    for (i = 0; i < szMatrix; i++){
        matrizA[i] =  (int*) malloc(sizeof(int)*szMatrix);
    }
    for (i = 0; i < szMatrix; i++){
        matrizB[i] = (int*) malloc(sizeof(int)*szMatrix);
    }
    for (i = 0; i < szMatrix; i++){
        matrizC[i] = (int*) malloc(sizeof(int)*szMatrix);
    }
    inicializa_matriz_A();
    inicializa_matriz_B();

    //printf("%d\n", szMatrix);

    for (i = 0; i < szMatrix; i++){
        pthread_create(&tid[i], NULL, multiplica, (void *)(size_t)i);
    }
    for (i = 0; i < szMatrix; i++){
        pthread_join(tid[i], NULL);
    }
      
    
    pthread_mutex_destroy(&mutex);
    printMatrix();


}