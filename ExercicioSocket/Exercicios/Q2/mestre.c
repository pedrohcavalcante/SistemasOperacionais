// ## Mestre ## //
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

//#define szMat 3
#define BUFLEN 512

#define IP "127.0.0.1"





void preenche_matriz(int szMat, int (*matriz_1)[szMat], int (* matriz_2)[szMat] /*int ** matriz_3,*/ ){
	for (int i = 0; i < szMat; i++) {
		for (int j = 0; j < szMat; j++) {
			matriz_1[i][j] = rand() % 100;
		}
	}
	for (int i = 0; i < szMat; i++) {
		for (int j = 0; j < szMat; j++) {
			matriz_2[i][j] = rand() % 100;
		}
	}
	/*for (int i = 0; i < szMat; i++) {
		for (int j = 0; j < szMat; j++) {
			matriz_3[i][j] = 0;
		}
	}*/
}

void print_matrix(int szMat, int (*matriz_1)[szMat], int (* matriz_2)[szMat]){
	printf("Matriz_1\n");
	for (int i = 0; i < szMat; i++) {
		for (int j = 0; j < szMat; j++) {
			printf("[%d][%d]=%d ", i, j, matriz_1[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Matriz_2\n");
	for (int i = 0; i < szMat; i++) {
		for (int j = 0; j < szMat; j++) {
			printf("[%d][%d]=%d ", i, j, matriz_2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	/*printf("Matriz_3\n");
	for (int i = 0; i < szMat; i++) {
		for (int j = 0; j < szMat; j++) {
			printf("[%d][%d]=%d ", i, j, Matrix_resultado_mult[i][j]);
		}
		printf("\n");
	}*/
}

int main(int argc, char *argv[]){
	//printf("Porta: %d", atoi(argv[1]));
	struct sockaddr_in escravo_1, escravo_2, escravo_3;
	int soquete_1, soquete_2, soquete_3, soquete_aux;

	//Portas
	int porta_1 = atoi(argv[1]);
	int porta_2 = porta_1 + 1;
	int porta_3 = porta_2 + 1;

	// Tamanho da Matriz
	int szMat = atoi(argv[2]);

	int matriz_1[szMat][szMat];
	int matriz_2[szMat][szMat];
	int matriz_3[szMat][szMat];
	int Matrix_resultado_mult[szMat][szMat];

	printf("Porta 1: %d\n", porta_1);
	printf("Porta 2: %d\n", porta_2);
	printf("Porta 3: %d\n", porta_3);

	// Sock
	socklen_t slen_1 = sizeof(escravo_1);
	socklen_t slen_2 = sizeof(escravo_2);
	socklen_t slen_3 = sizeof(escravo_3);

	char buf[BUFLEN]; 

	// Definindo Sockets
	soquete_1 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (soquete_1 == -1){
		printf("erro soquete_1");
	}

	soquete_2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (soquete_2 == -1){
		printf("erro soquete_2");
	}

	soquete_3 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (soquete_3 == -1){
		printf("erro soquete_3");
	}
	/*if ((soquete_1 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) == -1) || 
		(soquete_2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) == -1) || 
		(soquete_3 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) == -1)){
		printf("Erro na criação de alguns dos soquetes!");
		return 1;
	}*/


	memset((char*) &escravo_1, 0, sizeof(escravo_1));
	escravo_1.sin_family = AF_INET;
	escravo_1.sin_port = htons(porta_1);
	if (inet_aton (IP, &escravo_1.sin_addr) == 0){
		printf("Erro ao transformar endereço escravo_1\n");
		return 1;
	}

	memset((char*) &escravo_2, 0, sizeof(escravo_2));
	escravo_2.sin_family = AF_INET;
	escravo_2.sin_port = htons(porta_2);
	if (inet_aton (IP, &escravo_2.sin_addr) == 0){
		printf("Erro ao transformar endereço escravo_2\n");
		return 1;
	}


	memset((char*) &escravo_3, 0, sizeof(escravo_3));
	escravo_3.sin_family = AF_INET;
	escravo_3.sin_port = htons(porta_3);
	if (inet_aton (IP, &escravo_3.sin_addr) == 0){
		printf("Erro ao transformar endereço escravo_3\n");
		return 1;
	}

	srand(time(NULL));

	preenche_matriz(szMat, matriz_1, matriz_2);

	/*print_matrix();*/

	// Como já possuo código do envio de vetores, para facilitar o desenvolvimento vou transformar
	// cada linha da matriz em um vetor;

	int* vetor_A;
	int* vetor_B;
	int* vetor_C;

	vetor_A = malloc (sizeof(int) * szMat);
	vetor_B = malloc (sizeof(int) * szMat);
	vetor_C = malloc (sizeof(int) * szMat);


	// Associando matriz A

	for (int i = 0; i < szMat; i++){
		for (int j = 0; j < szMat; j++){
			if (i == 0){
				vetor_A[j] = matriz_1[i][j];
			}else if(i == 1){
				vetor_B[j] = matriz_1[i][j];
			}else{
				vetor_C[j] = matriz_1[i][j];
			}
		}
	}


	// Enviando dados para os escravos;

	// Enviando tamanho da matriz

	if (sendto(soquete_1, &szMat, sizeof(int), 0, (struct sockaddr *) &escravo_1, slen_1) == -1){
		printf("Erro ao enviar tamanho do vetor ao escravo 1\n");
	}

	if (sendto(soquete_2, &szMat, sizeof(int), 0, (struct sockaddr *) &escravo_2, slen_2) == -1){
		printf("Erro ao enviar tamanho do vetor ao escravo 2\n" );
	}

	if (sendto(soquete_3, &szMat, sizeof(int), 0, (struct sockaddr *) &escravo_3, slen_3) == -1){
		printf("Erro ao enviar tamanho do vetor ao escravo 3\n" );
	}

	//Colunas

	if(sendto(soquete_1, vetor_A, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_1, slen_1) == -1) {
		printf("Erro ao enviar pacote coluna vetor A.\n");
		return 1;
	}

	if(sendto(soquete_2, vetor_B, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_2, slen_2) == -1) {
		printf("Erro ao enviar pacote coluna vetor B\n" );
		return 1;
	}
	if(sendto(soquete_3, vetor_C, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_3, slen_3) == -1){ 	
		printf("Erro ao enviar pacote coluna vetor c\n" );
		return 1;
	}

	// Associando matriz B

	for (int i = 0; i < szMat; i++) {
		for (int j = 0; j < szMat; j++) {
			if (j == 0) {
				vetor_A[i] = matriz_2[i][j];
			}
			else if (j == 1) {
				vetor_B[i] = matriz_2[i][j];
			}
			else {
				vetor_C[i] = matriz_2[i][j];
			} 
		}
	}

	// Linhas
	// Escravo 1
	if (sendto(soquete_1, vetor_A, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_1, slen_1) == -1) {
		printf("Erro ao enviar pacote Escravo 1 vetor A.\n");
		return 1;
	}
	// Escravo 1
	if (sendto(soquete_2, vetor_A, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_2, slen_2) == -1) {
		printf("Erro ao enviar pacote Escravo 2 vetor A.\n");
		return 1;
	}
	// Escravo 1
	if (sendto(soquete_3, vetor_A, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_3, slen_3) == -1) {
		printf("Erro ao enviar pacote Escravo 3 vetor A.\n");
		return 1;
	}
	// Escravo 2
	if (sendto(soquete_1, vetor_B, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_1, slen_1) == -1) {
		printf("Erro ao enviar pacote Escravo 1 vetor B.\n");
		return 1;
	}
	// Escravo 2
	if (sendto(soquete_2, vetor_B, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_2, slen_2) == -1) {
		printf("Erro ao enviar pacote Escravo 2 vetor B.\n");
		return 1;
	}
	// Escravo 2
	if (sendto(soquete_3, vetor_B, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_3, slen_3) == -1) {
		printf("Erro ao enviar pacote Escravo 3 vetor B.\n");
		return 1;
	}

	// Escravo 3
	if (sendto(soquete_1, vetor_C, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_1, slen_1) == -1) {
		printf("Erro ao enviar pacote Escravo 1 vetor C.\n");
		return 1;
	}
	// Escravo 3
	if (sendto(soquete_2, vetor_C, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_2, slen_2) == -1) {
		printf("Erro ao enviar pacote Escravo 2 vetor C.\n");
		return 1;
	}
	// Escravo 3
	if (sendto(soquete_3, vetor_C, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_3, slen_3) == -1) {
		printf("Erro ao enviar pacote Escravo 3 vetor C.\n");
		return 1;
	}

	free(vetor_A);
	free(vetor_B);
	free(vetor_C);

	int vetor_resultante_A[szMat];
	int vetor_resultante_B[szMat];
	int vetor_resultante_C[szMat];

	recvfrom(soquete_1, &vetor_resultante_A, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_1, &slen_1);
  	for (int i = 0; i < szMat; i++) {
	  	printf("Pacote recebido de %s: %d\nDado: %d\n", inet_ntoa(escravo_1.sin_addr), ntohs(escravo_1.sin_port), vetor_resultante_A[i]);
  	}
  	close(soquete_1);

 	recvfrom(soquete_2, &vetor_resultante_B, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_2, &slen_2);
  	for (int i = 0; i < szMat; i++) {
	  	printf("Pacote recebido de %s: %d\nDado: %d\n", inet_ntoa(escravo_2.sin_addr), ntohs(escravo_2.sin_port), vetor_resultante_B[i]);
  	}
  	close(soquete_2);

 	recvfrom(soquete_3, &vetor_resultante_C, sizeof(int) * szMat, 0, (struct sockaddr *) &escravo_3, &slen_3);
   	for (int i = 0; i < szMat; i++) {
	 	printf("Pacote recebido de %s: %d\nDado: %d\n", inet_ntoa(escravo_3.sin_addr), ntohs(escravo_3.sin_port), vetor_resultante_C[i]);
  	}
  	close(soquete_3);

  	

  	// Como anteriormente foi quebrada a matriz em vetores, agora vamos juntar os vetores em uma matriz;

  	for (int i = 0; i < szMat; i++) {
  		for (int j = 0; j < szMat; j++) {
  			if (i == 0) {
  				Matrix_resultado_mult[i][j] = vetor_resultante_A[j];
  			}
  			else if (i == 1) {
  				Matrix_resultado_mult[i][j] = vetor_resultante_B[j];
  			}
  			else {
  				Matrix_resultado_mult[i][j] = vetor_resultante_C[j];
  			}
  		}
	}

	for (int i = 0; i < szMat; i++) {
		for (int j = 0; j < szMat; j++) {
			printf("[%d][%d]=%d ", i, j, Matrix_resultado_mult[i][j]);
		}
		printf("\n");
	}
	print_matrix(szMat, matriz_1, matriz_2);

	return 0;

}