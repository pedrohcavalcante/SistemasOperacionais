/****************** SERVER CODE ****************/
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

int main(){
	
  struct sockaddr_in servidor, cliente;
  int s, i;
  socklen_t slen_s=sizeof(servidor);
  socklen_t slen_c=sizeof(cliente);
  char buf[BUFLEN];
  if ((s=socket(AF_INET, SOCK_DGRAM, IP PROTO_UDP))==-1){
    printf("ERRO NA CRICAO DO SOCKET");
    return 1;
  }
  memset((char*) &servidor, 0, sizeof(servidor));
  servidor.sin_family = AF_INET;
  servidor.sin_port = htons(PORT);
  printf("Setando porta para: %d\n", PORT);
  servidor.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(s, (struct sockaddr *) &servidor, sizeof(servidor))==-1){
    printf("ERRO NO BINDING");
    return 1;
  }

  for(i=0;i<PACOTES;i++){

    if(recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &cliente, &slen_c)==-1){
      printf("ERRO AO RECEBER DADO");
      return 1;
    }
    printf("Pacote recebido de %s:%d\nDado: %s\n", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port), buf);
  }

  sendto(s, "Obrigado!", 10, 0, (struct sockaddr *)&cliente, slen_c);
	

  return 0;
}
