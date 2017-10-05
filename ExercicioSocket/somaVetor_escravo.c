/****************** ESCRAVO ****************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFLEN 512

int main(int argc, char *argv[]){
	
  struct sockaddr_in mestre;
  int s, i;
  socklen_t slen=sizeof(mestre);
  char buf[BUFLEN];
  int PORT = atoi(argv[1]);
  int vetorSize;
  
  if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
    printf("ERRO NA CRICAO DO SOCKET");
    return 1;
  }
  
  memset((char*) &mestre, 0, sizeof(mestre));
  mestre.sin_family = AF_INET;
  mestre.sin_port = htons(PORT);
  mestre.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(s, (struct sockaddr *) &mestre, sizeof(mestre))==-1){
    printf("ERRO NO BINDING");
    return 1;
  }

  
	
  if (recvfrom(s, &vetorSize, sizeof(int), 0, (struct sockaddr *)(size_t) &mestre, &slen)== -1){
    printf("Erro ao receber tamanho\n");
    return 1;
  }


  int vetor[vetorSize], soma=0;

  for(i = 0;i < vetorSize; i++){
    vetor[i]=-1;
  }


	if(recvfrom(s, &vetor, sizeof(int)*vetorSize, 0, (struct sockaddr *) &mestre, &slen)==-1){
		printf("ERRO AO RECEBER DADO");
		return 1;
	}
  for(i = 0;i < vetorSize; i++){
    printf("Pacote recebido de %s:%d\nDado: %d\n", inet_ntoa(mestre.sin_addr), htons(mestre.sin_port), vetor[i]);
  }
	

  
  for(i = 0;i < vetorSize; i++){
    soma+=vetor[i];
  }
	  

  sprintf(buf, "Escravo na porta#%d: soma do vetor=%d", htons(mestre.sin_port), soma);
  sendto(s, buf, BUFLEN, 0, (struct sockaddr *)&mestre, slen);
	

  return 0;
}
