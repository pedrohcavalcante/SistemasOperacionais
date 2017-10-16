#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFLEN 512
#define szMatrix 3

int* MultiplicaMatrix (int* coluna, int* linha_1, int* linha_2, int* linha_3, int* resultado) {
	for (int i = 0; i < szMatrix; i++) {
		for (int j = 0; j < szMatrix; j++) {
			if (i == 0) {
				resultado[i] += coluna[j]*linha_1[j];
			}
			else if (i == 1) {
				resultado[i] += coluna[j]*linha_2[j];	
			}
			else {
				resultado[i] += coluna[j]*linha_3[j];
			}
		}
	}
	return resultado;
}

int main (int argc, char * argv[]) {
	
	struct sockaddr_in mestre;
	int soquete_do_resultado;

	
	socklen_t slen = sizeof(mestre);
	char buf[BUFLEN];
	
	int port = atoi(argv[1]);
	
	int vetor_col[szMatrix];


	int vetor_A[szMatrix];
	int vetor_B[szMatrix];
	int vetor_C[szMatrix];
	int vetor_Final[szMatrix];
	
	soquete_do_resultado = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (soquete_do_resultado == -1) {
		printf("Erro na criacao do socket.\n");
		return 1;
	}
	memset((char*) &mestre, 0, sizeof(mestre));
	mestre.sin_family = AF_INET;
	mestre.sin_port = htons(port);
	mestre.sin_addr.s_addr = htonl (INADDR_ANY);

	if (bind(soquete_do_resultado, (struct sockaddr *) &mestre, sizeof(mestre)) == -1) {
		printf("Erro no binding.\n");
		return 1;
	}

	if (recvfrom(soquete_do_resultado, &vetor_col, sizeof(int) * szMatrix, 0, (struct sockaddr *) &mestre, &slen) == -1) {
		printf("Erro ao receber linha.\n");
	}

	for (int i = 0; i < szMatrix; i++) {
		printf("PACOTE RECEBIDO DE %s: %d\nDADO: %d\n", inet_ntoa(mestre.sin_addr), htons(mestre.sin_port), vetor_col[i]);
	}

	if (recvfrom(soquete_do_resultado, &vetor_A, sizeof(int) * szMatrix, 0, (struct sockaddr *) &mestre, &slen) == -1) {
		printf("Erro ao receber matriz.\n");
	}

	for (int i = 0; i < szMatrix; i++) {
		printf("PACOTE RECEBIDO DE %s: %d\nDADO: %d\n", inet_ntoa(mestre.sin_addr), htons(mestre.sin_port), vetor_A[i]);
	}

	if (recvfrom(soquete_do_resultado, &vetor_B, sizeof(int) * szMatrix, 0, (struct sockaddr *) &mestre, &slen) == -1) {
		printf("Erro ao receber matriz.\n");
	}

	for (int i = 0; i < szMatrix; i++) {
		printf("PACOTE RECEBIDO DE %s: %d\nDADO: %d\n", inet_ntoa(mestre.sin_addr), htons(mestre.sin_port), vetor_B[i]);
	}

	if (recvfrom(soquete_do_resultado, &vetor_C, sizeof(int) * szMatrix, 0, (struct sockaddr *) &mestre, &slen) == -1) {
		printf("Erro ao receber matriz.\n");
	}

	for (int i = 0; i < szMatrix; i++) {
		printf("PACOTE RECEBIDO DE %s: %d\nDADO: %d\n", inet_ntoa(mestre.sin_addr), htons(mestre.sin_port), vetor_C[i]);
	}
	
	sendto(soquete_do_resultado, MultiplicaMatrix(vetor_col, vetor_A, vetor_B, vetor_C, vetor_Final), sizeof(int) * szMatrix, 0, (struct sockaddr *) &mestre, slen);

	return 0;
}