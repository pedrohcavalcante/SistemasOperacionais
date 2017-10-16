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

int main(int argc, char * argv[]){
	struct sockaddr_in mestre;
	int sock_res;

	socklen_t slen = sizeof(mestre);
	char buf[BUFLEN];

	int port = atoi(argv[1]);
	int vetor[szMatrix];
	int vetor_1[szMatrix];
	int vetor_2[szMatrix];
	int vetor_3[szMatrix];
	int vetor_final[szMatrix];

	sock_res = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock_res == -1) {
		printf("Erro na criacao do socket.\n");
		return 1;
	
	}

	memset((char*) &mestre, 0, sizeof(mestre));
	mestre.sin_family = AF_INET;
	mestre.sin_port = htons(port);
	mestre.sin_addr.s_addr = htonl (INADDR_ANY);

	if (bind(sock_res, (struct sockaddr *) &mestre, sizeof(mestre)) == -1) {
		printf("Erro no binding.\n");
		return 1;
	}	
}