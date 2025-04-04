#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;
    
    printf("Exemplo de redirecionamento com pipes (simulando 'ls | wc -l')\n");
    
    // Criar o pipe
    if (pipe(pipefd) == -1) {
        perror("Erro ao criar pipe");
        exit(EXIT_FAILURE);
    }
    
    // Criar o primeiro processo filho (para executar 'ls')
    pid1 = fork();
    
    if (pid1 < 0) {
        perror("Erro ao criar o primeiro processo");
        exit(EXIT_FAILURE);
    }
    
    if (pid1 == 0) {
        // Código do primeiro filho (ls)
        
        // Redirecionar a saída padrão para o pipe
        close(pipefd[0]);  // Fechar o lado de leitura
        dup2(pipefd[1], STDOUT_FILENO);  // Saída padrão → lado de escrita do pipe
        close(pipefd[1]);  // Fechar o descritor original
        
        // Executar 'ls'
        execlp("ls", "ls", NULL);
        
        // Se chegar aqui, houve erro
        perror("Erro ao executar ls");
        exit(EXIT_FAILURE);
    }
    
    // Criar o segundo processo filho (para executar 'wc -l')
    pid2 = fork();
    
    if (pid2 < 0) {
        perror("Erro ao criar o segundo processo");
        exit(EXIT_FAILURE);
    }
    
    if (pid2 == 0) {
        // Código do segundo filho (wc -l)
        
        // Redirecionar a entrada padrão para o pipe
        close(pipefd[1]);  // Fechar o lado de escrita
        dup2(pipefd[0], STDIN_FILENO);  // Entrada padrão ← lado de leitura do pipe
        close(pipefd[0]);  // Fechar o descritor original
        
        // Executar 'wc -l'
        execlp("wc", "wc", "-l", NULL);
        
        // Se chegar aqui, houve erro
        perror("Erro ao executar wc");
        exit(EXIT_FAILURE);
    }
    
    // Código do processo pai
    // Fechar ambos os lados do pipe, pois o pai não os utiliza
    close(pipefd[0]);
    close(pipefd[1]);
    
    // Esperar pelos processos filhos
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    printf("Ambos os processos filhos terminaram\n");
    
    return 0;
}