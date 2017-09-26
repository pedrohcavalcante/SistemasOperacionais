/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORTA 5555
int main(){
  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  //cria o socket
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  //seta informacoes pertinentes a conexao
  serverAddr.sin_family = AF_INET;//conexao internet
  serverAddr.sin_port = htons(PORTA);//numero da porta
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//endereco IP (localhost)
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);//adiciona 0

  addr_size = sizeof serverAddr;
  //conecta ao servidor
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  recv(clientSocket, buffer, 1024, 0);//recebe mensagem do servidor

  printf("Data received: %s",buffer);//imprime a mensagem

  return 0;
}
