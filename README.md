# Programação de Sistemas em C na Prática - System Calls (Chamadas de Sistema)

Este repositório contém exemplos de código C para ilustrar o uso de system calls em Linux.

## Estrutura do Projeto

* `src/`: Arquivos de código-fonte C.
* `Makefile`: Arquivo para automatizar a compilação.
* `CMakeLists.txt`: Arquivo de configuração do CMake para build multiplataforma

## Instruções para Compilar o Projeto

### **Compilando Usando o Make**

Um arquivo `Makefile` é utilizado para automatizar o processo de compilação do projeto. Siga os passos abaixo para compilar.

#### Pré-requisitos:
1. **Certifique-se de que o Make está instalado no sistema**:
    - Verifique com: `make --version`.
    - Instale, caso necessário:
        - **Ubuntu/Linux:** `sudo apt-get install make`
        - **macOS:** `xcode-select --install`

2. **Entre no diretório raiz do projeto**:
   ```bash
   cd /caminho/para/o/projeto
   ```

#### Comando para compilar:
1. Compile o projeto:
   ```bash
   make
   ```
    - Este comando utiliza as instruções contidas no arquivo `Makefile` para compilar o código.

2. Para **limpar os arquivos gerados** (se configurado no `Makefile`):
   ```bash
   make clean
   ```
    - Remove arquivos temporários, como objetos (`*.o`) e binários.

### **Compilando Usando o CMake**

O `CMake` é uma ferramenta de build multiplataforma. Siga os passos abaixo.

#### Pré-requisitos:
1. **Certifique-se de que o CMake está instalado no sistema**:
    - Verifique com: `cmake --version`.
    - Instale, caso necessário:
        - **Ubuntu/Linux:** `sudo apt-get install cmake`
        - **macOS:** Utilize o Homebrew: `brew install cmake`

2. **Entre no diretório raiz do projeto**:
   ```bash
   cd /caminho/para/o/projeto
   ```

#### Etapas para compilar com o CMake:
1. **Crie um diretório para os arquivos de build**:
    - Por convenção, crie e acesse o diretório para compilação:
      ```bash
      mkdir build && cd build
      ```

2. **Gere os arquivos de build**:
    - Execute o seguinte comando no diretório `build`:
      ```bash
      cmake ..
      ```
    - O `..` indica que o arquivo `CMakeLists.txt` está no diretório pai (raiz do projeto).

3. **Compile o projeto**:
    - Em seguida, execute o comando:
      ```bash
      cmake --build .
      ```
    - Isso compila o projeto e gera o executável na pasta de saída configurada pelo `CMakeLists.txt` (geralmente o próprio diretório `build`).

4. **Executar o programa compilado**:
    - Localize o executável gerado no diretório `build` e execute:
      ```bash
      ./nome_do_programa
      ```

### **Erros Comuns e Dicas**

1. **Falhas no `make` ou `cmake`**:
    - Revise os arquivos `Makefile` ou `CMakeLists.txt` para garantir que os caminhos e dependências estão corretos.

2. **Dependências de bibliotecas ausentes**:
    - Pode ser necessário instalar bibliotecas adicionais. Verifique instruções/documentações no repositório (como o `README.md`).

3. **Modo Verbose no CMake**:
    - Para depurar problemas de compilação, utilize o modo verbose no CMake:
      ```bash
      cmake --build . -- VERBOSE=1
      ```

    - Isso exibe os comandos completos de compilação.
