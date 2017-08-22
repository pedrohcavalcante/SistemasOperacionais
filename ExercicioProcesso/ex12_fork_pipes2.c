   #include <sys/wait.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>
   #include <string.h>
   #define MAX_SIZE 4

   int main(int argc, char * argv[])
   {
       int vetor_pipe_ida[2], vetor_pipe_volta[2];
       pid_t pid;
       char buffer[MAX_SIZE];
	int num, resposta;

       pipe(vetor_pipe_ida); // cria o pipe
       pipe(vetor_pipe_volta); // cria o pipe
       pid = fork(); // cria um novo processo
       if (pid == 0) // se é o processo-filho
       {

           close(vetor_pipe_ida[1]); // fecha o caminho de escrita pois não será utilizado pelo filho
           while (read(vetor_pipe_ida[0], buffer, MAX_SIZE) > 0); // leia enquanto nao for o fim (EOF)
	   
	   sscanf(buffer, "%d", &num);	
           close(vetor_pipe_ida[0]); // fecha o caminho de leitura do pipe
           printf("FILHO: O filho leu: %d\n", num);
	   
	   num = num +1;
	   sprintf(buffer, "%d", num);
	 
           close(vetor_pipe_volta[0]); // fecha o caminho de leitura pois nao será utilizado
           
	   write(vetor_pipe_volta[1],  buffer, MAX_SIZE); // envia o conteúdo do parametro passado pelo pipe
           close(vetor_pipe_volta[1]); // fecha o caminho de escrita do pipe
           
	   printf("FILHO: O filho escreveu: %d\n", num);
	   printf("FILHO: O filho terminou\n");
           
	   exit(EXIT_SUCCESS); // termina o processo filho
       }
       else // se for o processo-pai
       {
	   num = atoi(argv[1]);   
	   sprintf(buffer, "%d", num);
           close(vetor_pipe_ida[0]); // fecha o caminho de leitura pois nao será utilizado
           write(vetor_pipe_ida[1], buffer, MAX_SIZE); // envia o conteúdo do parametro passado pelo pipe
           close(vetor_pipe_ida[1]); // fecha o caminho de escrita caracterizando o fim (EOF)
	   printf("PAI: O pai escreveu: %s\n", buffer);
           
           close(vetor_pipe_volta[1]); // fecha o caminho de escrita do pipe
	   while (read(vetor_pipe_volta[0], buffer, MAX_SIZE) > 0) // leia enquanto nao for o fim (EOF)
           close(vetor_pipe_volta[0]); // fecha o caminho de leitura do pipe
	   sscanf(buffer, "%d", &num);	
	   printf("PAI: O pai leu: %d\n", num);
           
	   wait(NULL); // espera até que o filho termine
	   printf("PAI: O filho terminou\n");
	   printf("PAI: O pai terminou\n");
           exit(EXIT_SUCCESS);
       }
       return 0;
   }
