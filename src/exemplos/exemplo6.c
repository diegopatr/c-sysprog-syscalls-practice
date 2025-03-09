/*
 * Este programa demonstra como utilizar a chamada de sistema `execve` 
 * para substituir a imagem do processo atual por uma nova imagem de 
 * processo, em conjunto com a chamada de sistema `write` para escrever 
 * mensagens na saída padrão.
 * 
 * Funcionalidades principais:
 * - Escreve uma mensagem na saída padrão utilizando `write`.
 * - Substitui o processo atual pelo programa `/bin/ls` utilizando `execve`.
 * - Passa argumentos ao programa `ls` para listar em formato detalhado 
 *   (`-l`) e incluir arquivos ocultos (`-a`).
 * 
 * Caso `execve` falhe:
 * - Exibe uma mensagem de erro na saída padrão de erro.
 * - Retorna um código de saída diferente de zero.
 *
 * Conceito-chave:
 * - A chamada `execve` não cria um novo processo, mas substitui o atual.
 *   Caso `execve` falhe, a execução continuará no código após a chamada.
 *
 * Observação:
 * - Este programa utiliza `NULL` como vetor de variáveis de ambiente,
 *   fazendo com que o processo herdado receba o ambiente do processo pai.
 */
#include <unistd.h> // Fornece acesso às funções da API POSIX, como write e execve.
#include <string.h> // Fornece funções de manipulação de strings, como strlen.
#include <stdlib.h> // Fornece funções gerais, como exit.
#include <stdio.h>  // Fornece funções para entrada e saída padrão, como perror.

int main()
{
    // Ponteiro para uma string contendo uma mensagem que será escrita na saída padrão.
    char* msg = "\n\nHello, World!\n\n";

    // Caminho para o programa `ls`, que lista arquivos de um diretório.
    // `/bin/ls` é a localização padrão do binário `ls` em sistemas Unix-like.
    char* progname = "/bin/ls";

    // Um array de argumentos que será passado ao programa `ls`.
    // - `argv[0]`: Nome do programa que está sendo executado (por convenção, o próprio progname).
    // - `argv[1]`: Opção `-l`, que solicita o formato de listagem detalhado.
    // - `argv[2]`: Opção `-a`, que solicita que arquivos ocultos também sejam listados.
    // - `argv[3]`: NULL indica o fim da lista de argumentos.
    char* argv[] = {progname, "-l", "-a", NULL};

    // Um array de variáveis de ambiente para o novo programa.
    // - Aqui, é configurado como `NULL`, o que indica que o programa herda
    //   o ambiente do chamador.
    char* envp[] = {NULL};

    // Escreve a mensagem (`msg`) na saída padrão (descritor de arquivo 1).
    // - `1`: descritor de arquivo para a saída padrão.
    // - `msg`: ponteiro para a string contendo a mensagem.
    // - `strlen(msg)`: calcula o tamanho da string para determinar o número de bytes a serem escritos.
    write(1, msg, strlen(msg));

    // Substitui a imagem de processo atual por uma nova imagem de processo (`/bin/ls`).
    // - `progname`: Caminho para o arquivo executável.
    // - `argv`: Lista de argumentos passados ao novo programa.
    // - `envp`: Variáveis de ambiente passadas ao novo programa.
    if (execve(progname, argv, envp) == -1)
    {
        // Caso `execve` falhe, uma mensagem de erro será exibida na saída padrão de erro.
        perror("Erro ao executar o programa /bin/ls");

        // Retorna um código de saída diferente de zero para indicar falha.
        exit(EXIT_FAILURE);
    }

    // Esta parte nunca será alcançada, pois `execve` substitui a imagem do processo.
    printf("Essa mensagem não deveria ser exibida.");
    return EXIT_SUCCESS;
}