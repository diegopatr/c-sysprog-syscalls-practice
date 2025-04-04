#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

int main() {
    int pipefd[2];  // Array para armazenar os descritores do pipe
    pid_t pid;
    char buffer[BUFFER_SIZE];
    
    printf("Exemplo de comunicação entre processos usando pipes\n");
    
    // Criar o pipe
    if (pipe(pipefd) == -1) {
        perror("Erro ao criar pipe");
        exit(EXIT_FAILURE);
    }
    
    // Criação do processo filho
    pid = fork();
    
    if (pid < 0) {
        perror("Erro ao criar processo");
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) {
        // Código do processo pai
        printf("Processo pai (PID: %d): Escrevendo no pipe\n", getpid());
        
        // Fechar o lado de leitura do pipe (não será usado pelo pai)
        close(pipefd[0]);
        
        // Escrever uma mensagem no pipe
        const char *mensagem = "Olá, processo filho! Esta mensagem foi enviada pelo pipe.";
        write(pipefd[1], mensagem, strlen(mensagem) + 1);
        printf("Processo pai: Mensagem enviada: \"%s\"\n", mensagem);
        
        // Fechar o lado de escrita após terminar
        close(pipefd[1]);
        
        // Esperar pelo término do filho
        wait(NULL);
        printf("Processo pai: Filho terminou a execução\n");
    }
    else {
        // Código do processo filho
        printf("Processo filho (PID: %d): Lendo do pipe\n", getpid());
        
        // Fechar o lado de escrita do pipe (não será usado pelo filho)
        close(pipefd[1]);
        
        // Ler a mensagem do pipe
        ssize_t num_bytes = read(pipefd[0], buffer, BUFFER_SIZE);
        
        if (num_bytes > 0) {
            printf("Processo filho: Mensagem recebida (%ld bytes): \"%s\"\n", 
                   (long)num_bytes, buffer);
        } else {
            printf("Processo filho: Nenhum dado recebido\n");
        }
        
        // Fechar o lado de leitura após terminar
        close(pipefd[0]);
        
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}