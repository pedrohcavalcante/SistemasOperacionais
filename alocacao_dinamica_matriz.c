#include <stdio.h>
#include <stdlib.h>

int **matriz_global;

int main(int argc, char* argv[] ){
	int M=atoi(argv[1]);
	int i, j;
	matriz_global = (int **)malloc(sizeof(int*)*M);
	for(i=0;i<M;i++)
		matriz_global[i] = (int*) malloc(sizeof(int)*M);
	for(i=0;i<M;i++)
		for(j=0;j<M;j++)
			matriz_global[i][j]=666;

	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			printf("%d ", matriz_global[i][j]);
		}
		printf("\n");
	}

	return 0;
}
