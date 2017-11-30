#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	if (argc == 1){
		printf(argv[0]);
		printf("Por favor, submeta o nome do arquivo. O programa está sendo encerrado\n");
		return 0;
	}
	FILE *arq;
	//char url[] = argv[1];
	char url[] = "arqexemplo";
	arq = fopen(url, "r");
	if (arq == NULL){
		printf("Erro ao abrir\n");
	}else{
		printf("oie\n");
	}
}