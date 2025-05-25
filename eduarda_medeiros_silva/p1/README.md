[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/3XHcMjDV)

# Projeto Compilador, Assembler e Executor

Este projeto consiste na implementação de três componentes principais: um **compilador**, um **assembler** e um **executor** simples, desenvolvidos como parte de um estudo de caso ou projeto acadêmico para fins educativos. O foco deste trabalho está em entender como diferentes camadas de tradução e execução de código funcionam, com ênfase em uma linguagem de máquina fictícia, bem como nas etapas de compilação e execução de código de baixo nível.

## Estrutura do Projeto

O projeto é dividido em três componentes principais, que são os responsáveis pela transformação e execução do código.

### Componentes do Projeto

1. **Compilador**: Converte código escrito em uma linguagem intermediária para uma linguagem de máquina específica. No nosso caso, o compilador traduz um código de uma linguagem fictícia de alto nível para instruções que podem ser processadas pelo nosso assembler e executadas pela máquina fictícia.

2. **Assembler**: Recebe o código de máquina gerado pelo compilador e o converte para um formato de assembly. O objetivo do assembler é gerar código que pode ser lido e interpretado mais facilmente, de acordo com uma linguagem de baixo nível (um código mais próximo do hardware).

3. **Executor**: Simula a execução do código gerado, interpretando as instruções de máquina ou de assembly e simulando como um processador fictício executaria essas instruções.

### Estrutura de Pastas

```
/pasta raiz
│
├── assem/
│   ├── assembler.c      # Implementação do assembler
│   └── assembler.h      # Cabeçalho do assembler
│
├── exec/
│   ├── executor.c       # Implementação do executor
│   └── executor.h       # Cabeçalho do executor
│
├── comp/
│   ├── compilador.c     # Implementação do compilador
│   └── compilador.h     # Cabeçalho do compilador
│
├── Makefile             # Arquivo para construção dos executáveis
└── gramatica.pdf        # Gramática reconhecida pelo compilador
└── assembler.pdf        # Descrição da gramática implementada no assembler
└── README.md            # Este arquivo
```

## Como Usar

1. **Clonar o Repositório**:

   Para começar, clone o repositório para sua máquina local:

   ```bash
   git clone [URL do repositório]
   cd [diretório do repositório]
   ```

2. **Construção dos Executáveis**:

   O `Makefile` está configurado para compilar e gerar os três executáveis necessários: **compilador**, **assembler** e **executor**. Para construir os executáveis, basta rodar o comando:

   ```bash
   make
   ```

   Este comando irá compilar os arquivos `.c` de cada um dos componentes e gerar os executáveis:

   - `compilador`
   - `assembler`
   - `executor`

3. **Rodando os Programas**:

   Após a construção, você pode rodar os programas gerados da seguinte forma:

   - Para rodar o **compilador**:

     ```bash
     ./compilador programa.lpn
     ```

   - Para rodar o **assembler**:

     ```bash
     ./assembler programa.asm
     ```

   - Para rodar o **executor**:

     ```bash
     ./executor programa.mem
     ```


4. **Limpeza**:

   Para remover os executáveis gerados e limpar a pasta do projeto, use o comando:

   ```bash
   make clean
   ```

## Detalhamento de Cada Componente

### 1. Compilador

O compilador é responsável por pegar o código de entrada escrito em uma linguagem intermediária e gerar um código de máquina, que é compatível com a arquitetura da máquina fictícia utilizada no projeto. Ele processa o código linha por linha, identifica os tokens, e os traduz para as instruções do nosso conjunto de instruções (mnemônicos).

**Exemplo de entrada para o compilador**:
```text
DATA var1, 10
CODE
LDA var1
ADD 5
HLT
```

**Como funciona**:
- O compilador lê o arquivo de entrada e divide em tokens.
- Os tokens são analisados e convertidos para instruções de máquina correspondentes.
- Nessa implementação, o compilador só faz as instruções de máquina para soma e subtração.

### 2. Assembler

O assembler pega o código de máquina gerado pelo compilador e o converte para uma versão em **assembly**, mais legível. Ele realiza a tradução para os mnemônicos que descrevem as operações de forma mais amigável.

**Exemplo de entrada para o assembler**:
O código de máquina gerado pelo compilador seria convertido para um arquivo de assembly, com instruções como `LDA`, `ADD`, etc.

### 3. Executor

O executor simula a execução do código gerado. Ele pega o código de máquina ou de assembly, carrega as instruções na memória e executa-as de acordo com a lógica do processador fictício.

**Como funciona**:
- O executor lê o código gerado, armazena as instruções na memória.
- Ele simula o ciclo de execução de um processador, executando as instruções de forma sequencial, respeitando o fluxo de controle (por exemplo, saltos condicionais e loops).