// ### Server ###
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

#define szVetor 10

#define porta1 4445
#define porta2 4446

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
    
}