#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

void print(int total, int *chamadas){
	for (int i = 0; i < total; i++){
		printf("%d ", chamadas[i]);
	}
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
int cmpfuncDesc (const void * a, const void * b) {
   return !( *(int*)a - *(int*)b );
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

	for (int i = 0; i < total-1; i++){
		if (chamadas[i] < chamadas[i+1]){
			cilindros += chamadas[i+1] - chamadas[i];
		}else{
			cilindros += chamadas[i] - chamadas[i+1];
		}
	}
	printf("\n");
	printf("Cilindros: %d\n\n", cilindros);
	
}
void doSSTF(int posInicial, int total, int *chamadas){
	int VetFinal[total+1];
	printf("SSTF\n");
	VetFinal[0] = posInicial;
	
	int j = 0;
	int cilindros;
	int distancia = 0;
	int proximo;
	for (int i = 0; i < total; i++){
		VetFinal[i+1] = chamadas[i];
	}

	
	int posMenor;
	
	int posAtual = VetFinal[0];
	int vetOrdenado[total+1];
	printf("Ordem: ");
	for (int i = 1; i <= total+1; i++){
		printf("%d ", posAtual);
			vetOrdenado[i] = posAtual;
		int menorDistancia = INT_MAX;

		for (j = 1; j <= total+1; j++){
			if (posAtual - VetFinal[j] < 0){

				distancia = VetFinal[j] - posAtual;
				if (distancia < menorDistancia){
					if (VetFinal[j] != -1){
						menorDistancia = distancia;
						proximo = j;
					}
					
				}
		
			}else{
				distancia = posAtual - VetFinal[j];	
				if (distancia < menorDistancia){
					if (VetFinal[j] != -1){
						menorDistancia = distancia;
						proximo = j;
					}
				}
			}

		}
		
		posAtual = VetFinal[proximo];
		VetFinal[proximo] = -1;
	}
	printf("\n");

	for (int i = 1; i <= total; i++){
		if ( vetOrdenado[i] <  vetOrdenado[i+1]){
			cilindros +=  vetOrdenado[i+1] -  vetOrdenado[i];
		}else{
			cilindros +=  vetOrdenado[i] -  vetOrdenado[i+1];
		}
	}
	printf("Cilindros: %d\n", cilindros);
	printf("\n");
}
void doScanDOWN(int posInicial, int total, int *chamadas){

	printf("Scan Desce\n");
	
	int vetorOrdenado[total+1];
	int sizeMenores = 0;
	int sizeMaiores = 0;
	for (int i = 0; i < total; i++){
		if (chamadas[i] < posInicial){
			sizeMenores++;
		}else{
			sizeMaiores++;
		}
	}

	int vetorMenores[sizeMenores];
	int vetorMaiores[sizeMaiores];
	

	for (int i = 0; i < sizeMenores; i++){
		for(int j = 0; j < total; j++){
			if (chamadas[j] <= posInicial){
				vetorMenores[i] = chamadas[j];
				i++;
			}
		}
	}

	for (int i = 0; i < sizeMaiores; i++){
		for(int j = 0; j < total; j++){
			if (chamadas[j] > posInicial){
				vetorMaiores[i] = chamadas[j];
				i++;
			}
		}
	}

	qsort(vetorMenores, sizeMenores, sizeof(int), cmpfuncDesc);
	qsort(vetorMaiores, sizeMaiores, sizeof(int), cmpfunc);
	vetorOrdenado[0] = posInicial;
	for (int i = 0; i < total;){
		for (int j = 0; j < sizeMenores; j++){
			vetorOrdenado[i+1] = vetorMenores[j];
			i++;
		}
		for (int k = 0; k < sizeMaiores; k++){
			vetorOrdenado[i+1] = vetorMaiores[k];
			i++;
		}

	}
	printf("Ordem: ");
	print(total+1, vetorOrdenado);
	int cilindros = 0;
	for (int i = 1; i <= total; i++){
		if ( vetorOrdenado[i] <  vetorOrdenado[i+1]){
			cilindros +=  vetorOrdenado[i+1] -  vetorOrdenado[i];
		}else{
			cilindros +=  vetorOrdenado[i] -  vetorOrdenado[i+1];
		}
	}
	printf("\n");
	printf("Cilindros: %d\n", cilindros);

	printf("\n");

}

void doScanUP(int posInicial, int total, int *chamadas){
	printf("Scan Sobe\n");
	
	int vetorOrdenado[total+1];
	int sizeMenores = 0;
	int sizeMaiores = 0;
	for (int i = 0; i < total; i++){
		if (chamadas[i] < posInicial){
			sizeMenores++;
		}else{
			sizeMaiores++;
		}
	}

	int vetorMenores[sizeMenores];
	int vetorMaiores[sizeMaiores];
	

	for (int i = 0; i < sizeMenores; i++){
		for(int j = 0; j < total; j++){
			if (chamadas[j] <= posInicial){
				vetorMenores[i] = chamadas[j];
				i++;
			}
		}
	}

	for (int i = 0; i < sizeMaiores; i++){
		for(int j = 0; j < total; j++){
			if (chamadas[j] > posInicial){
				vetorMaiores[i] = chamadas[j];
				i++;
			}
		}
	}
	qsort(vetorMenores, sizeMenores, sizeof(int), cmpfuncDesc);
	qsort(vetorMaiores, sizeMaiores, sizeof(int), cmpfunc);
	vetorOrdenado[0] = posInicial;
	for (int i = 0; i < total;){
		for (int k = 0; k < sizeMaiores; k++){
			vetorOrdenado[i+1] = vetorMaiores[k];
			i++;
		}
		for (int j = 0; j < sizeMenores; j++){
			vetorOrdenado[i+1] = vetorMenores[j];
			i++;
		}
		

	}
	printf("Ordem: ");
	print(total+1, vetorOrdenado);
	int cilindros = 0;
	for (int i = 1; i <= total; i++){
		if ( vetorOrdenado[i] <  vetorOrdenado[i+1]){
			cilindros +=  vetorOrdenado[i+1] -  vetorOrdenado[i];
		}else{
			cilindros +=  vetorOrdenado[i] -  vetorOrdenado[i+1];
		}
	}
	printf("\n");
	printf("Cilindros: %d\n", cilindros);

	printf("\n");


}



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
	doScanDOWN(posicaoInicial, total, chamadas);
	doScanUP(posicaoInicial, total, chamadas);


}