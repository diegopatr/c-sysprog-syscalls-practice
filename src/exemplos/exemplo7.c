/*
* Este programa é uma implementação em C de um utilitário básico para
 * copiar o conteúdo de um arquivo de entrada para um arquivo de saída.
 *
 * Funcionalidades principais:
 * - Abre um arquivo de entrada em modo somente leitura;
 * - Cria (ou sobrescreve) um arquivo de saída com permissões padrão e
 *   gravação habilitada;
 * - Lê dados do arquivo de entrada em blocos e os escreve no arquivo de saída;
 * - Garante o tratamento de erros, como falhas ao abrir, ler, escrever ou
 *   fechar arquivos.
 *
 * Uso:
 * ./programa <arquivo_entrada> <arquivo_saida>
 * - <arquivo_entrada>: Caminho para o arquivo existente que será lido.
 * - <arquivo_saida>: Caminho para o arquivo onde o conteúdo será copiado.
 *
 * Nota:
 * Caso ocorra algum erro, uma mensagem descritiva será exibida e o programa
 * será encerrado imediatamente.
 */
#include <fcntl.h>  // Manipulação de arquivos (open, flags, etc.)
#include <stdio.h>  // Entrada e saída padrão (printf, fprintf, etc.)
#include <stdlib.h> // Funções utilitárias (malloc, free, exit, etc.)
#include <unistd.h> // Operações relacionadas ao sistema POSIX (read, write, close, etc.)

// Constantes
const int BUFFER_SIZE =
    1024; // Define o tamanho do buffer para leitura/escrita.
const int DEFAULT_FILE_PERMISSIONS =
    0644; // Define as permissões padrão para novos arquivos criados.

// Função para lidar com erros
void handle_error(const char* error_message)
{
    // Exibe uma mensagem de erro descritiva com base no valor de errno.
    perror(error_message);
    // Sai do programa indicando falha.
    exit(EXIT_FAILURE);
}

// Função para abrir arquivos de forma genérica
int open_file(const char* filename, int flags, int permissions)
{
    // Tenta abrir o arquivo com os parâmetros fornecidos.
    int file_descriptor = open(filename, flags, permissions);

    // Verifica se houve erro ao abrir o arquivo.
    if (file_descriptor == -1)
    {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", filename);
        // Sai do programa em caso de erro.
        exit(EXIT_FAILURE);
    }
    return file_descriptor; // Retorna o descritor do arquivo aberto.
}

// Função para copiar conteúdo de um arquivo para outro
void copy_content(int input_file_descriptor, int output_file_descriptor)
{
    char read_buffer[BUFFER_SIZE]; // Define o buffer de leitura
    ssize_t bytes_read;

    // Lê dados do arquivo de entrada em blocos e grava no arquivo de saída.
    while ((bytes_read = read(input_file_descriptor, read_buffer,
                              sizeof(read_buffer))) > 0)
    {
        if (write(output_file_descriptor, read_buffer, bytes_read) == -1)
        {
            handle_error("Erro ao copiar o conteúdo."); // Trata erro na escrita do arquivo.
        }
    }
    // Verifica erro durante a leitura.
    if (bytes_read == -1)
    {
        handle_error("Erro na leitura do conteúdo.");
    }

    // Exibe uma mensagem indicando que a cópia foi concluída com sucesso.
    printf("Cópia concluída com sucesso!\n");
}

// Função para fechar arquivos
void close_file(int file_descriptor)
{
    // Verifica se houve erro ao tentar fechar o arquivo.
    if (close(file_descriptor) == -1)
    {
        handle_error("Erro ao fechar o arquivo.");
    }
}

int main(int argc, char* argv[])
{
    // Verifica se os parâmetros necessários foram fornecidos.
    if (argc < 3)
    {
        fprintf(stderr, "Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Abrir o arquivo de entrada fornecido como argumento em modo somente-leitura
    // (O_RDONLY).
    int input_file_descriptor = open_file(argv[1], O_RDONLY, 0);
    // Abrir/criar o arquivo de saída fornecido como argumento com acesso de
    // escrita, truncando-o se já existir, e usando permissões padrão para o novo
    // arquivo.
    int output_file_descriptor = open_file(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
                                           DEFAULT_FILE_PERMISSIONS);

    // Copiar o conteúdo do arquivo de entrada para o arquivo de saída.
    copy_content(input_file_descriptor, output_file_descriptor);

    // Fechar os arquivos após realizar as operações.
    close_file(input_file_descriptor);
    close_file(output_file_descriptor);

    // Retorna sucesso ao final da execução do programa.
    return EXIT_SUCCESS;
}
