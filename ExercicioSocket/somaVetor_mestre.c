/****************** MESTRE ****************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFLEN 512
#define PACOTES 10
#define SRV_IP "127.0.0.1"

int main(int argc, char *argv[]){
  int size = atoi(argv[3]);
  printf("tamanho do vetor: %d", size);
  struct sockaddr_in escravoA, escravoB;
  int sock_A, sock_B, i;
  socklen_t slen_A=sizeof(escravoA);
  socklen_t slen_B=sizeof(escravoB);
  char buf[BUFLEN]; 
  int PORT_A=atoi(argv[1]);
  int PORT_B=atoi(argv[2]);
  int vetorA[size];
  int vetorB[size];
  
  if((sock_A=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
    printf("ERRO AO CRIAR SOCKET\n");
    return 1;
  }
  if((sock_B=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
    printf("ERRO AO CRIAR SOCKET\n");
    return 1;
  }

  memset((char*) &escravoA, 0, sizeof(escravoA));
  escravoA.sin_family = AF_INET;
  escravoA.sin_port = htons(PORT_A);
  if(inet_aton(SRV_IP, &escravoA.sin_addr) == 0){
    printf("ERRO AO TRANSFORMAR ENDEREÇO\n");
    return 1;
  }
  
  memset((char*) &escravoB, 0, sizeof(escravoB));
  escravoB.sin_family = AF_INET;
  escravoB.sin_port = htons(PORT_B);
  if(inet_aton(SRV_IP, &escravoB.sin_addr) == 0){
    printf("ERRO AO TRANSFORMAR ENDEREÇO\n");
    return 1;
  }

  for(i = 0;i < size; i++){
    vetorA[i]=1;
    vetorB[i]=2;
  }

  printf("Enviando tamanho do vetor para escravo A\n");
  if(sendto(sock_A, &size, sizeof(int), 0, (struct sockaddr *) &escravoA, slen_A)==-1){
    printf("Erro ao enviar tamanho\n");
    return 1;
  }

  printf("Enviando tamanho do vetor para escravo B\n");
  if(sendto(sock_B, &size, sizeof(int), 0, (struct sockaddr *) &escravoB, slen_B)==-1){
    printf("Erro ao enviar tamanho\n");
    return 1;
  }



	printf("Enviando o vetorA\n");
  if(sendto(sock_A, &vetorA, sizeof(int)*size, 0, (struct sockaddr *) &escravoA, slen_A)==-1){
    printf("ERRO AO ENVIAR PACOTE\n");
    return 1;
  }
	printf("Enviando o vetorB\n");
  if(sendto(sock_B, &vetorB, sizeof(int)*size, 0, (struct sockaddr *) &escravoB, slen_B)==-1){
		printf("ERRO AO ENVIAR PACOTE\n");
		return 1;
	}
	
  recvfrom(sock_A, buf, BUFLEN, 0, (struct sockaddr *) &escravoA,&slen_A);
  printf("Pacote recebido de %s:%d\nDado: %s\n", inet_ntoa(escravoA.sin_addr), ntohs(escravoA.sin_port),  buf);
  close(sock_A);
  
  recvfrom(sock_B, buf, BUFLEN, 0, (struct sockaddr *) &escravoB,&slen_B);
  printf("Pacote recebido de %s:%d\nDado: %s\n", inet_ntoa(escravoB.sin_addr), ntohs(escravoB.sin_port), buf);
  close(sock_B);

  return 0;
}
