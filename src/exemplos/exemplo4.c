/*
 * Este programa cria um diretório chamado "testeaula" no diretório temporário do sistema `/tmp`.
 *
 * Funcionalidades principais:
 * - Utiliza a chamada de sistema `mkdir` para criar o diretório.
 * - Configura as permissões do diretório como 0777, que permitem leitura, escrita e execução para todos os usuários.
 * - Verifica o sucesso ou falha da criação do diretório, exibindo mensagens apropriadas ao usuário.
 *
 * Detalhes:
 * - Se bem-sucedido, o programa informa que o diretório foi criado.
 * - Caso ocorra uma falha, o programa exibe uma mensagem de erro e o valor retornado pela chamada `mkdir`.
 *
 * Nota:
 * O diretório `/tmp` é tradicionalmente usado para armazenar arquivos ou diretórios temporários em sistemas Unix/Linux.
 */

#include <stdio.h>      // Inclui a biblioteca padrão de entrada e saída para funções como printf.
#include <sys/stat.h>   // Inclui a biblioteca para chamadas relacionadas ao sistema de arquivos, como mkdir.

int main(int argc, char **argv) {
    // Declara uma variável inteira `s` que armazenará o valor de retorno da chamada de sistema `mkdir`.
    int s;

    // Exibe uma mensagem informando ao usuário que o diretório "testeaula" está sendo criado em `/tmp`.
    printf("Criando diretório testeaula em /tmp\n");

    // Chama a função `mkdir` para criar o diretório `/tmp/testeaula`.
    // O segundo argumento `0777` define as permissões padrão do diretório:
    // - Leitura, escrita e execução para o dono, grupo e outros (777 em octal).
    s = mkdir("/tmp/testeaula", 0777);

    // Verifica o valor de retorno da função `mkdir`.
    // - Se `mkdir` retornar 0 (zero): o diretório foi criado com sucesso.
    if (!s)
        // Exibe uma mensagem informando que o diretório foi criado.
        printf("Diretorio criado\nConferir...\n");
    else
        // Caso contrário, exibe uma mensagem de erro com o valor de retorno de `mkdir`.
        // Embora `mkdir` normalmente retorne `-1` em caso de erro, exibimos aqui o valor armazenado em `s`.
        printf("Problema ao criar diretório. Retorno %d\n", s);

    // Retorna 0 para indicar que o programa foi executado com sucesso.
    return(0);
}