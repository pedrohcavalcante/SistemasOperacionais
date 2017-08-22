   #include <sys/wait.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>
   #include <string.h>

   int main(int argc, char * argv[])
   {
       int vetor_pipe[2];
       pid_t pid;
       char buffer[10];

       pipe(vetor_pipe); // cria o pipe
       pid = fork(); // cria um novo processo
       if (pid == 0) // se é o processo-filho
       {
           close(vetor_pipe[1]); // fecha o caminho de escrita pois não será utilizado pelo filho
           while (read(vetor_pipe[0], &buffer, 10) > 0) // leia enquanto nao for o fim (EOF)
           close(vetor_pipe[0]); // fecha o caminho de leitura do pipe
	   printf("FILHO: O filho terminou e leu: %s\n", buffer);
           exit(EXIT_SUCCESS); // termina o processo filho
       }
       else // se for o processo-pai
       {
           close(vetor_pipe[0]); // fecha o caminho de leitura pois nao será utilizado
           write(vetor_pipe[1], argv[1], strlen(argv[1])); // envia o conteúdo do parametro passado pelo pipe
           close(vetor_pipe[1]); // fecha o caminho de escrita caracterizando o fim (EOF)
	   printf("PAI: O pai terminou e escreveu: %s\n", argv[1]);
           wait(NULL); // espera até que o filho termine
	   printf("PAI: O filho terminou\n");
           exit(EXIT_SUCCESS);
       }
       return 0;
   }
