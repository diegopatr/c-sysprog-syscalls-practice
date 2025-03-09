cmake_minimum_required(VERSION 3.30.5)
project(c-sysprog-syscalls-practice C)

set(CMAKE_C_STANDARD 11)

# Define as flags de compilação
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

# Adiciona o diretório include ao path de inclusão
include_directories(include)

# Define os diretórios de código-fonte
set(DIR_EXEMPLOS src/exemplos)

# Cria os executáveis para os exemplos
file(GLOB_RECURSE EXEMPLOS_SRC "${DIR_EXEMPLOS}/*.c")
foreach(SRC_FILE IN LISTS EXEMPLOS_SRC)
    get_filename_component(EXECUTABLE_NAME ${SRC_FILE} NAME_WE) # Extrai o nome do arquivo sem extensão
    add_executable(${EXECUTABLE_NAME} ${SRC_FILE})
endforeach()
