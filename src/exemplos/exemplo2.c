/*
 * Este programa simples exemplifica o uso da chamada de sistema `write`
 * para exibir a mensagem "Hello, World!" na saída padrão (stdout) sem 
 * utilizar funções de biblioteca como `printf`. 
 * 
 * Destaques do programa:
 * - O programa utiliza diretamente a chamada de sistema `write`.
 * - Escreve a mensagem na saída padrão (descritor de arquivo 1).
 * - Demonstra como trabalhar com escrita em nível mais baixo no sistema operacional,
 *   sem usar abstrações fornecidas pela biblioteca padrão.
 */

#include <unistd.h> // Inclui a biblioteca POSIX para acesso à chamada de sistema 'write'.

int main(void) { // Função principal do programa; não recebe argumentos.
    // Chama a função `write` para enviar a mensagem "Hello, World!\n" para a saída padrão.
    // Argumentos da chamada `write`:
    //   1  -> O número 1 representa o descritor de arquivo para a saída padrão (stdout).
    //   "Hello, World!\n" -> A string a ser escrita na saída (inclui o caractere de nova linha '\n').
    //   14 -> O tamanho da string (14 caracteres), incluindo o caractere de nova linha.
    write(1, "Hello, World!\n", 14);

    // Retorna 0 para indicar que o programa foi executado com sucesso.
    return 0;
}