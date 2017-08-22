#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char * argv[]){

    int number = atoi(argv[1]);

    pid_t filhinho_querido;
    //printf("oi");
    int pipe1[2], pipe2[2];
    //Criando pipes
    if (pipe(pipe1) < 0){
        perror("Oxente, erro no pipe1");
        return -1;
    }
    if (pipe(pipe2) < 0){
        perror("Oxente, erro no pipe2");
        return -1;
    }

    //Criando filho
    filhinho_querido = fork();
    //processo do pai
    if (filhinho_querido < 0){
        printf("ERRO");
    }else if (filhinho_querido > 0){
        //incrementa o numero
        number++;

        //fechando processo
        close(pipe1[0]);

        write(pipe1[1], &number, sizeof(number));

        //recebendo
        close(pipe2[1]);
        read(pipe2[0], &number, sizeof(number));
        printf(">>> Luke, I'm your father! And I have your number: %d\n", number);
    }else if (filhinho_querido == 0){
        close(pipe1[1]);
        read(pipe1[0], &number, sizeof(number));

        printf(">>> I'm Luke and I have the number: %d\n", number);
        printf(">>> I'm Luke Agora eu vou incrementar o numero: %d\n", number++); 
        printf(">>> I'm Luke Agora eu vou enviar de volta ao meu pai\n");
        close(pipe2[0]);
        write(pipe2[1], &number, sizeof(number));
        printf(">>> I'm Luke Adeus, munto cruel\n");
    }

    return 0;

}