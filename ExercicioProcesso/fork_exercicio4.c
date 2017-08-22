#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t pid_filho1, pid_filho2;
	int i;
	pid_filho1 = fork();

        if (pid_filho1 <0){
		printf("Erro ao criar processo\n");
		return 1;
	}
	else if(pid_filho1 == 0){
		printf("\nFILHO 1 foi criado\n");
		for(i=100;i<=199;i++){
			printf("[PID=%D;PID_DO_PAI=%d] %d\n", getpid(), getppid(), i);
			sleep(1);
		}
		printf("\nFILHO 1 vai morrer\n");
		
	}
	else{
		pid_filho2 = fork();
		if(pid_filho2 == 0){
			printf("\nFILHO 2 foi criado\n");
			for(i=200;i<=299;i++){
				printf("[PID=%D;PID_DO_PAI=%d] %d\n", getpid(), getppid(), i);
				sleep(1);
			}
			printf("\nFILHO 2 vai morrer\n");
			
		}
		else{
			for(i=1;i<=50;i++){
				printf("[PID=%D;PID_DO_PAI=%d] %d\n", getpid(), getppid(), i);
				sleep(2);
			}
			printf("\nProcesso PAI vai morrer\n");
		}
	}
	return 0;
}

