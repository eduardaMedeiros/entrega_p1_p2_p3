# Interpretador e Gerador de Brainfuck
Este projeto consiste em dois programas escritos em C:

* **bfc**: Um compilador que transforma expressões matemáticas simples em código Brainfuck que, ao ser executado, imprime o resultado da expressão no terminal.

* **bfe**: Um interpretador Brainfuck que executa qualquer código escrito na linguagem Brainfuck.

### 🔢 bfc (Brainfuck Compiler)

O `bfc` lê uma entrada no formato:

```
label=expressao
```

Exemplo:

```
resultado=2+3*4
```

Ele realiza duas tarefas principais:

1. **Cálculo da expressão:**
   Implementa um parser simples que lê a expressão da direita (após o `=`) e executa as operações na ordem em que aparecem, **sem considerar precedência de operadores**. Por exemplo, `2+3*4` será interpretado como `(2+3)*4 = 20`.

2. **Geração de código Brainfuck:**
   O programa gera um código Brainfuck que, ao ser executado, imprime na tela:

```
resultado= 20
```

O gerador trata tanto caracteres ASCII simples quanto caracteres UTF-8 (dois bytes), convertendo-os em comandos que zeram a célula atual (`[-]`), aplicam o valor desejado (`+` repetido) e imprimem (`.`).

### 🧠 bfe (Brainfuck Executor)

O `bfe` é um interpretador completo da linguagem Brainfuck.

Funcionalidades:

* Suporte a todos os comandos básicos: `> < + - . , [ ]`.
* Implementação de laços com suporte a loops aninhados.

O interpretador lê um código Brainfuck da entrada padrão e executa.

## 🚀 Como compilar

### Requisitos:

* GCC ou outro compilador C compatível
* Make

### Passos:

Execute no terminal:

```bash
make
```

Isso irá gerar dois executáveis:

* `bfc`
* `bfe`

## 🧪 Como testar

### ✅ Execução direta

Você pode executar o gerador e o interpretador encadeando-os por pipe da seguinte forma:

```bash
echo "soma=10+5+7" | ./bfc | ./bfe
```

Saída esperada:

```
soma= 22
```

## 👨‍💻 Estrutura dos arquivos

* `bfc.c` — Gerador de código Brainfuck a partir de uma expressão matemática.
* `bfe.c` — Interpretador Brainfuck.
* `Makefile` — Automação de compilação.

Perfeito! Aqui está o README atualizado, refletindo corretamente que a execução é feita encadeando os dois programas (`bfc` e `bfe`) diretamente via pipe:


