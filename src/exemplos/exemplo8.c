#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Programa principal iniciado (PID: %d)\n", getpid());

    /* Exemplo 1: Apenas fork() */
    printf("\n--- Exemplo 1: Usando apenas fork() ---\n");
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("Erro ao criar processo");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        /* Código executado pelo processo filho */
        printf("Processo filho criado com fork (PID: %d, PPID: %d)\n",
               getpid(), getppid());
        printf("Filho executando o mesmo programa que o pai\n");
        exit(EXIT_SUCCESS);
    } else {
        /* Código executado pelo processo pai */
        printf("Processo pai criou filho com PID: %d\n", pid1);

        /* Esperar pelo filho terminar */
        int status;
        wait(&status);
        printf("Processo filho (PID: %d) terminou com status: %d\n",
               pid1, WEXITSTATUS(status));
    }

    /* Exemplo 2: fork() + exec() */
    printf("\n--- Exemplo 2: Usando fork() + exec() ---\n");
    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("Erro ao criar processo");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        /* Código executado pelo processo filho */
        printf("Processo filho criado para executar 'ls' (PID: %d)\n", getpid());

        /* Preparar argumentos para execve */
        char *args[] = {"ls", "-la", NULL};
        char *env[] = {NULL};

        /* Substituir o processo atual por 'ls -la' */
        execve("/bin/ls", args, env);

        /* Se chegou aqui, houve erro no exec */
        perror("Erro ao executar o comando");
        exit(EXIT_FAILURE);
    } else {
        /* Código executado pelo processo pai */
        printf("Processo pai criou filho com PID: %d para executar outro programa\n", pid2);

        /* Esperar pelo filho terminar */
        int status;
        wait(&status);
        printf("Processo filho (PID: %d) terminou com status: %d\n",
               pid2, WEXITSTATUS(status));
    }

    printf("\nPrograma principal terminado\n");
    return 0;
}