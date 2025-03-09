CC = gcc
CFLAGS = -Wall -g

# Define as variáveis para os diretórios
DIR_EXEMPLOS = src/exemplos
DIR_EXERCICIOS = src/exercicios
DIR_OUTPUT = build

# Cria o diretório de saída, se necessário
$(shell mkdir -p $(DIR_OUTPUT))

# Lista de todos os executáveis (exemplos e exercícios)
EXECUTAVEIS_EXEMPLOS = $(patsubst %.c,$(DIR_OUTPUT)/%,$(notdir $(wildcard $(DIR_EXEMPLOS)/*.c)))
EXECUTAVEIS_EXERCICIOS = $(patsubst %.c,$(DIR_OUTPUT)/%,$(notdir $(wildcard $(DIR_EXERCICIOS)/*.c)))
EXECUTAVEIS = $(EXECUTAVEIS_EXEMPLOS) $(EXECUTAVEIS_EXERCICIOS)

all: $(EXECUTAVEIS)

# Regra genérica para compilar os exemplos
$(DIR_OUTPUT)/%: $(DIR_EXEMPLOS)/%.c
	$(CC) $(CFLAGS) -Iinclude -o $@ $<

# Regra genérica para compilar os exercícios
$(DIR_OUTPUT)/%: $(DIR_EXERCICIOS)/%.c
	$(CC) $(CFLAGS) -Iinclude -o $@ $<

# Regra para limpar os arquivos compilados (exemplos e exercícios)
clean:
	rm -f $(DIR_OUTPUT)/*
	rmdir $(DIR_OUTPUT)

.PHONY: all clean
