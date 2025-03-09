/*
 * Este programa demonstra o uso direto da chamada de sistema `syscall`
 * para realizar operações de manipulação de arquivos no Linux.
 * Não utiliza funções de biblioteca comuns como `open`, `write` ou `close`.
 * Em vez disso, faz chamadas de sistema explícitas através de `syscall`.
 *
 * Funcionalidades implementadas:
 * - Cria ou abre um arquivo chamado "aula.txt" com permissões somente para o usuário.
 * - Escreve a string "Hello, World\n" dentro do arquivo.
 * - Fecha o arquivo após realizar a escrita.
 * - Sai do programa indicando sucesso (código de saída 0).
 *
 */

#include <unistd.h>    // Fornece acessos às chamadas de sistema e funções POSIX.
#include <sys/syscall.h> // Define símbolos para chamadas de sistema específicas.
#include <fcntl.h>      // Define constantes e flags para manipulação de arquivos.

int main() {
    // Chama o sistema operacional diretamente através de `syscall` para abrir/criar um arquivo.
    // `SYS_open`: Identifica a ação de abrir/criar um arquivo.
    // "aula.txt": Nome do arquivo que será manipulado.
    // `O_WRONLY | O_CREAT`: Indica que o arquivo será aberto em modo de escrita
    //                       e criado se não existir.
    // `S_IRUSR | S_IWUSR`: Define permissões para permitir leitura e escrita pelo usuário dono do arquivo.
    long arq = syscall(SYS_open, "aula.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    // Escreve a string "Hello, World\n" no arquivo previamente aberto.
    // `SYS_write`: Identifica a ação de escrita em um arquivo.
    // `arq`: File descriptor retornado pela chamada anterior (equivalente ao arquivo aberto).
    // "Hello, World\n": Mensagem que será escrita no arquivo.
    // `13`: Número de bytes a serem escritos no arquivo (tamanho da string, incluindo o "\n").
    syscall(SYS_write, arq, "Hello, World\n", 13);

    // Fecha o arquivo após a conclusão da escrita.
    // `SYS_close`: Identifica a ação de fechar um arquivo.
    // `arq`: File descriptor do arquivo a ser fechado.
    syscall(SYS_close, arq);

    // Encerra o programa explicitamente.
    // `SYS_exit`: Identifica a ação de terminar o programa.
    // `0`: Indica sucesso na execução do programa.
    syscall(SYS_exit, 0);
}