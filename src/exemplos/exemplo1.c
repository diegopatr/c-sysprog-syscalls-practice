/*
 * Este programa simples exibe a mensagem "Hello, World!" na saída padrão (geralmente o console).
 *
 * Funcionalidades principais:
 * - Utiliza a função `printf` da biblioteca padrão de entrada e saída para exibir texto.
 * - Retorna 0 para indicar ao sistema operacional que o programa foi executado com sucesso.
 *
 * Este é um exemplo clássico usado como introdução à linguagem C, por ser simples e eficiente para
 * iniciantes compreenderem a estrutura básica de um programa C.
 */

#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída para usar funções como `printf`.

int main(void) { // Função principal do programa; é o ponto de entrada de execução.
    // Exibe a mensagem "Hello, World!" seguida de uma nova linha '\n' na saída padrão.
    // `printf` é uma função que permite imprimir texto formatado no console.
    printf("Hello, World!\n");

    // Retorna 0 ao sistema operacional para indicar que o programa foi executado com sucesso.
    return 0;
}