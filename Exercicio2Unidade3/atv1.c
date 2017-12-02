#include <stdio.h>
#include <string.h>
#include <time.h>
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
	printf("SSTF\n");

	printf("Ordem: %d ", posInicial);
	int cilindros1, cilindros2;
	//int cilindroAtual = 0;
	int posAtual = posInicial;
	int j = 0;
	int cilindros;
	int cilindroInicial = 0;
	if (posInicial > chamadas[0]){
		cilindroInicial = posInicial - chamadas[0];
	}else{
		cilindroInicial = chamadas[0] - posInicial;
	}
	for (int i = 0; i < total; i++){
		for (int j = 0; j < total; j++){
			if (chamadas[i] < chamadas[j] && chamadas[i]-chamadas[j] < cilindroInicial){
				printf("IF\n");
				cilindroInicial = chamadas[i]-chamadas[j];
				posAtual = chamadas[j];
			}else if(chamadas[i] > chamadas[j] && chamadas[j]-chamadas[i] < cilindroInicial){
				printf("ELSE\n");
				cilindroInicial = chamadas[j] - chamadas[i];
				posAtual = chamadas[j];
			}
		}
		printf("%d ", posAtual);

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