#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 10
#define BUFFER_SAFRA 3

int buffer_index = 0;

void* produtor(int* buffer){
	int count=0;//contabiliza as SAFRAS
	while(count<BUFFER_SAFRA){
		
		/*aqui é preciso garantir que haja:
		1) haja escrita somente quando for possível (testar se buffer_index está dentro dos limites)
		2) se nao for possível, dormir...
		3) garantir que serão produzidas 3 "safras"
		4) imprimir quando houver produção e quando for dormir 
		*/
		
	}
	pthread_exit(NULL);
}

void* consumidor(int* buffer){
	int tmp; //armazena o que foi lido do buffer para que seja impresso 
	int count=0; //contabiliza as SAFRAS
	while(count<BUFFER_SAFRA){
		/*aqui é preciso garantir que:
		1) haja leitura escrita somente quando for possível (testar se buffer_index está dentro dos limites)
		2) se nao for possível, dormir...
		3) garantir que serão produzidas 3 "safras"
		4) imprimir quando houver consumo e quando for dormir 
		*/
	}
	pthread_exit(NULL);
}

int main(){
	pthread_t p, c;//threads do produtor e do consumidor
	int status, i;
	int *buffer = malloc(sizeof(int)*BUFFER_SIZE);//alocacao do buffer utilizado
	status = pthread_create(&p, NULL, (void*)produtor, buffer);//cria a thread do produtor
	status = pthread_create(&c, NULL, (void*)consumidor, buffer);//cria a thread do consumidor
	pthread_join(p, NULL);	//aguarda a finalização do produtor
	pthread_join(c, NULL);	//aguarda a finalização do consumidor
	printf("threads terminaram! Imprimindo o buffer:\n");
	printf("POSICAO | VALOR\n");
	for(i=0;i<BUFFER_SIZE;i++)
		printf("BUFFER[%d]: %d\n", i, buffer[i]);

	exit(EXIT_SUCCESS);
}
