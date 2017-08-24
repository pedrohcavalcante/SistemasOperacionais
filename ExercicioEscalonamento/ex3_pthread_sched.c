#include <pthread.h>
#include <stdio.h>
#define NTHREADS 5
#define ESCOLHIDA 2

static void display_sched_attr(int policy, struct sched_param *param){
           printf("    policy=%s, priority=%d\n",
                   (policy == SCHED_FIFO)  ? "SCHED_FIFO" :
                   (policy == SCHED_RR)    ? "SCHED_RR" :
                   (policy == SCHED_OTHER) ? "SCHED_OTHER" :
                   "???",
                   param->sched_priority);
}


void *runner(void *p){
        struct sched_param param;
	int policy;
	pthread_getschedparam(pthread_self(), &policy, &param);//obtem a politica de escalonamento e prioridade
	while(1)
		printf("Esta é a execucao da Thread #%d; Sua prioridade é %d\n", (int)(size_t) p, param.sched_priority); 
		

	pthread_exit(NULL);
}
	

int main(int argc, char *argv[]){
	
	int i, scope, r;
        int policy, s;
        struct sched_param param;
	pthread_t tid[NTHREADS];
	pthread_attr_t attr;

	pthread_attr_init(&attr);//inicializa a estrutura de dados de atributos
	
	s = pthread_getschedparam(pthread_self(), &policy, &param); //recebe qual é a politica atual e a prioridade
        printf("Prioridade minima=%d; Prioridade maxima=%d\n ", sched_get_priority_min(policy), sched_get_priority_max(policy) );

        display_sched_attr(policy, &param); //imprime qual o escalonamento e a prioridade


	for(i=0;i<NTHREADS;i++){
		if(i != ESCOLHIDA)//se não for a thread escolhida, tem a prioridade mais baixa...
			param.sched_priority = sched_get_priority_min(policy);
		else             //se for a escolhida, tem a prioridade mais alta
			param.sched_priority = sched_get_priority_max(policy);
		
		pthread_attr_setschedparam(&attr, &param);//seta o parametro
		pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);//garante que o escalonamento será herdado
		
		printf("CRIANDO Thread #%d; PRIORIDADE=%d\n", i, param.sched_priority);
		pthread_create(&tid[i], &attr, runner, (void*)(size_t)i);
	}

	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i], NULL);
	
	pthread_attr_destroy(&attr);//destroi a estrutura de dados de atributos

	return 0;
}
