#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

void calcCilindro(int total, int *chamadas){
	int cilindros;
	printf("%d\n", total);
	for (int i = 0; i < total-1; i++){
		if (chamadas[i] < chamadas[i+1]){
			cilindros += chamadas[i+1] - chamadas[i];
		}else{
			cilindros += chamadas[i] - chamadas[i+1];
		}
	}
	/*for (int i = 0; i <= total; i++){
		printf("=%d\n", chamadas[i]);
	}*/
	printf("\n");
	printf("Cilindros: %d\n\n", cilindros);
}

void doFCFS(int posInicial, int total, int *chamadas){
	printf("FCFS\n");
	int ordem[total+1];
	int cilindros = 0;
	if (posInicial < chamadas[0]){
		cilindros = chamadas[0] - posInicial;
	}else{
		cilindros = posInicial - chamadas[0];
	}
	
	printf("Ordem: %d ", posInicial);
	for (int i = 0; i < total; i++){
		printf("%d ", chamadas[i]);
		if (i == 0){
			ordem[i] = posInicial;
		}else{
			ordem[i] = chamadas[i];
		}
		
	}

	//calcCilindro(total+1, ordem);
	for (int i = 0; i < total-1; i++){
		if (chamadas[i] < chamadas[i+1]){
			cilindros += chamadas[i+1] - chamadas[i];
		}else{
			cilindros += chamadas[i] - chamadas[i+1];
		}
	}
	/*for (int i = 0; i <= total; i++){
		printf("=%d\n", ordem[i]);
	}*/
	printf("\n");
	printf("Cilindros: %d\n\n", cilindros);
	
}
void doSSTF(int posInicial, int total, int *chamadas){
	int VetFinal[total+1];
	printf("SSTF\n");
	VetFinal[0] = posInicial;
	//printf("Ordem: %d ", posInicial);
	//int cilindros1, cilindros2;
	//int cilindroAtual = 0;
	
	int j = 0;
	int cilindros;
	//int cilindroInicial = 0;
	int distancia = 0;
	int proximo;
	for (int i = 0; i < total; i++){
		VetFinal[i+1] = chamadas[i];
	}

	
	int posMenor;
	
	int posAtual = VetFinal[0];
	int vetOrdenado[total+1];

	for (int i = 0; i < total; i++){
		printf("PosAtual: %d\n", posAtual);
		int menorDistancia = INT_MAX;	

		for (j = 0; j < total; j++){
		
			if (posAtual - VetFinal[j] < 0){
		
				distancia = VetFinal[j] - posAtual;
				if (distancia < menorDistancia){
					menorDistancia = distancia;
					proximo = j;
				}
		
			}else{
		
				distancia = posAtual - VetFinal[j];	
				if (distancia < menorDistancia){
					menorDistancia = distancia;
					proximo = j;
				}
			}

		}
		vetOrdenado[i] = VetFinal[proximo];
		posAtual = VetFinal[proximo];
	}
	printf("\n");
}
void doScanDOWN();
void doScanUP();

int main(int argc, char *argv[]){

	FILE *arq;
	int aux = 0;

	if ((arq = fopen (argv[1], "r")) == NULL){
		printf("Hello darkness, my old friend");
	}

	char linha[50];

	int posicaoInicial; 
	int posicaoFinal;
	int total;

	if (fgets(linha, 50, arq) != NULL){
		posicaoInicial = atoi(linha);
	}

	if (fgets(linha, 50, arq) != NULL){
		total = atoi(linha);
	}

	int chamadas[total];

	if (fgets(linha, 50, arq) != NULL){
		char * quebra;
		quebra = strtok(linha, " ");
		while(quebra != NULL){

			chamadas[aux++] = atoi(quebra);

			quebra = strtok(NULL, " ");
		}
	}

	

	doFCFS(posicaoInicial, total, chamadas);
	doSSTF(posicaoInicial, total, chamadas);


}