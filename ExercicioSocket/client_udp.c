/****************** CLIENT CODE ****************/
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFLEN 512
#define PACOTES 10
#define PORT 4444
#define SRV_IP "127.0.0.1"

int main(int argc, char *argv[]){

  struct sockaddr_in servidor;
  int s, i;
  socklen_t slen=sizeof(servidor);
  char buf[BUFLEN];
  
  if((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
	printf("ERRO AO CRIAR SOCKET\n");
	return 1;
  }

  memset((char*) &servidor, 0, sizeof(servidor));
  servidor.sin_family = AF_INET;
  servidor.sin_port = htons(PORT);
  printf("Setando porta: %d\n",PORT);
  if(inet_aton(SRV_IP, &servidor.sin_addr) == 0){
	printf("ERRO AO TRANSFORMAR ENDEREÇO\n");
	return 1;
  }

  for(i=0;i<PACOTES;i++){
	printf("Enviando pacote %d\n", i);
        sprintf(buf, "Este é o pacote #%d\n", i);
        if(sendto(s, buf, BUFLEN, 0, (struct sockaddr *) &servidor, slen)==-1){
		printf("ERRO AO ENVIAR PACOTE\n");
		return 1;
	}
	
  }
  recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &servidor,&slen);
  printf("Pacote recebido de %s:%d\nDado: %s\n", inet_ntoa(servidor.sin_addr), ntohs(servidor.sin_port), buf);
  close(s);

  return 0;
}
