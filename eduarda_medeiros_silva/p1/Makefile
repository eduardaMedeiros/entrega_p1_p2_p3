CC = gcc
CFLAGS = -Wall -g -std=gnu99

# Executáveis que queremos gerar
EXECUTABLES = compilador assembler executor

# Arquivos fonte
SOURCES_COMPILADOR = comp/compilador.c
SOURCES_ASSEMBLER = assem/assembler.c
SOURCES_EXECUTOR = exec/executor.c

# Alvo principal
all: $(EXECUTABLES)

# Regras para compilar os executáveis diretamente
compilador: $(SOURCES_COMPILADOR)
	$(CC) $(CFLAGS) $^ -o $@

assembler: $(SOURCES_ASSEMBLER)
	$(CC) $(CFLAGS) $^ -o $@

executor: $(SOURCES_EXECUTOR)
	$(CC) $(CFLAGS) $^ -o $@

# Limpeza
clean:
	rm -f $(EXECUTABLES)
