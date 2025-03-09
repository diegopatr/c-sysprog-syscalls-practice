/*
 * Este programa demonstra o uso de sinais no sistema operacional para realizar uma tarefa periódica.
 * Ele utiliza o sinal `SIGALRM` (alarme) para executar uma ação a cada intervalo de 5 segundos,
 * imprimindo o timestamp atual (em segundos desde o Epoch) na tela.
 *
 * Funcionalidades principais:
 * - Define uma função de tratamento para o sinal `SIGALRM` usando `signal`.
 * - Utiliza as chamadas de sistema `alarm` e `pause` para repetir a tarefa indefinidamente.
 * - Exibe mensagens na saída padrão para indicar o funcionamento do programa.
 *
 * Funcionamento:
 * - O programa entra em um loop infinito, onde a cada 5 segundos recebe o sinal de alarme.
 * - Quando o sinal é recebido, uma mensagem com o timestamp atual é exibida.
 */

#include <unistd.h>   // Para chamadas de sistema POSIX como alarm() e pause().
#include <stdio.h>    // Para funções padrão de entrada e saída, como printf().
#include <time.h>     // Para manipulação de tempo, como time() e time_t.
#include <signal.h>   // Para manipulação de sinais, como signal() e SIGALRM.

// Função que trata o sinal SIGALRM
void mensagem() {
    time_t tp;              // Declara uma variável para armazenar o tempo atual.
    time(&tp);              // Obtém o tempo atual do sistema e armazena em 'tp'.
    printf("%ld\n", (long)tp);  // Imprime o timestamp (tempo em segundos desde 01/01/1970) na saída padrão.
}

// Função principal - ponto de entrada do programa
int main(int argc, char **argv) {
    // Registra a função 'mensagem' como tratadora para o sinal SIGALRM.
    // Sempre que o sinal SIGALRM for recebido, a função 'mensagem' será executada.
    signal(SIGALRM, mensagem);

    // Exibe uma mensagem indicando o início do programa na saída padrão.
    printf("*** Início do programa\n");

    // Loop infinito para manter o programa em execução.
    while (1) {
        alarm(5);    // Configura o alarme para enviar o sinal SIGALRM após 5 segundos.
        pause();     // Suspende a execução do programa até que um sinal (neste caso, SIGALRM) seja recebido.
        printf("Executando\n");  // Após a recepção e tratamento do sinal, exibe "Executando".
    }

    return 0;  // (Nunca alcançado devido ao loop infinito, mas geralmente indica término bem-sucedido do programa.)
}