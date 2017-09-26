/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORTA 5555

int main(){
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t addr_size;

  //Cria o socket TCP
  welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  //seta informações pertinentes a conexao
  serverAddr.sin_family = AF_INET;//conexao internet
  serverAddr.sin_port = htons(5555);//numero da porta
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //endereco IP (localhost)
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //adiciona 0 

  //faz o bind do socket, caracterizando-o
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  //O socket entra em modo passivo esperando conexoes
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  
  addr_size = sizeof(clientAddr);
  //aceita uma nova conexao
  newSocket = accept(welcomeSocket, (struct sockaddr *) &clientAddr, &addr_size);

  //escreve no buffer a mensagem a ser enviada
  strcpy(buffer,"Hello World\n");
  send(newSocket,buffer,13,0);//envia a mensagem

  return 0;
}
