#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void No(int noAtual, int maxNo, int numFilhos, int numeroNo, int aux){
	// Testa se o nó atual é o nó maximo. 
	if (noAtual == maxNo){
		exit(0);
	}

    noAtual++;
    printf(">>> (%d)Pid atual: %d com pid do pai:  %d\n",noAtual, getpid(), getppid());

    for (int i = 0; i < numFilhos; i++){
        pid_t Filhinho_querido = fork();
        if (Filhinho_querido < 0){
            printf(">>> AVISO: não foi possível criar o processo.");
            exit(1);
        }

        if (Filhinho_querido == 0){
            No(noAtual, maxNo, numFilhos, aux + i, aux + i);
        }else{
            wait(NULL);
        }
    }
}

int main(int argc, char * argv[]){
    int maxNo = atoi(argv[1]);
    //scanf("%d", &maxNo);

    No(0, maxNo, 1, 0, 0);
	
    return 0;
}
