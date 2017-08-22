#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include <string.h>

void* thread_function(void)
{
    char *hello = malloc(sizeof(char) * 10);
    strcpy(hello,"hello world");
    pthread_exit((void*)hello);
}
int main()
{
    pthread_t tid;
    char *saida;

    pthread_create(&tid, NULL,(void*)thread_function, NULL);

    pthread_join(tid,(void**)&saida);
    printf("Thread terminou e retornou: %s\n",saida); 
    free(saida);

}
