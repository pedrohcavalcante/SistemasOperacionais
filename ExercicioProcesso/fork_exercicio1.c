#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t pid_terminado, pid_do_filho1, pid_do_filho_filho1, pid_do_filho2, pid_do_filho_filho2;
	printf("O pai iniciou sua execucao (PID=%d)\n", getpid());
	pid_do_filho1 = fork();
/*a partir daqui temos dois processos executando*/

        if (pid_do_filho1 <0){
		printf("Erro ao criar processo\n");
		return 1;
	}
	else if(pid_do_filho1 == 0){
		printf("Esta é a execução do filho1 (PID=%d)\n", getpid());
		pid_do_filho_filho1 = fork();
/*a partir daqui temos dois processos executando*/
		if(pid_do_filho_filho1 == 0){
			printf("Esta é a execucao do filho do filho1 (PID=%d)\n", getpid());
			printf("Filho do Filho1 terminou!\n");
			exit(0);
		}
		else{
		/*aqui quem executa é o filho1*/
			printf("Filho1 terminou!\n");
			exit(0);
		}

	}
	else{

/*aqui somente o pai executa*/
		pid_do_filho2 = fork();
		
		if(pid_do_filho2 == 0){
			printf("Esta é a execução do filho2 (PID=%d)\n", getpid());
			pid_do_filho_filho2 = fork();
			if(pid_do_filho_filho2 == 0){
				printf("Esta é a execucao do filho do filho2 (PID=%d)\n", getpid());
				/*aqui executa o filho do filho 2*/
				printf("Filho do Filho2 terminou!\n");
				exit(0);
			}		
			else{
				printf("Filho2 terminou!\n");
				exit(0);
			}	
			
		}
		else{
		/*aqui quem executa é o processo pai*/
			wait(NULL);
			printf("Pelo menos 1 processos-filho finalizou\n");
			//printf("1 processo-filho finalizou\n");
			//pid_terminado = waitpid(pid_do_filho2, NULL, 0);
			//printf("processo-filho #%d finalizou\n", pid_terminado);
			printf("Pai terminou!\n");
			exit(0);

		}
	}
	return 0;
}

