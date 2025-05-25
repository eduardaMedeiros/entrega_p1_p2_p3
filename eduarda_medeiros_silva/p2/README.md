Perfeito! Aqui está um modelo de **README.md** bem estruturado, explicando a gramática de forma clara, profissional e organizada:
# 📄 Gramática da Linguagem "PROGRAMA"

## 🧠 **Descrição Geral**

A linguagem **PROGRAMA** possui uma estrutura simples, onde um programa é iniciado por um cabeçalho, seguido pelo bloco principal com comandos e finalizado com uma palavra-chave de encerramento.

### Estrutura básica de um programa:

```plaintext
PROGRAMA "NomeDoPrograma":
INICIO
    <corpo do programa>
FIM
```

## 🔧 **Componentes da Linguagem**

### ✅ **Delimitadores do Programa**

* **PROGRAMA "nome":** → Define o cabeçalho do programa.
* **INICIO** → Marca o início dos comandos.
* **FIM** → Finaliza o programa.

### 🔤 **Declaração de Variáveis**

```plaintext
<tipo> <identificador> (= <expressao>)?
```

Exemplos:

```plaintext
int contador
float media = 5.5
```

### 🧠 **Atribuição**

```plaintext
<identificador> = <expressao>
```

Exemplo:

```plaintext
contador = contador + 1
```

### 🔂 **Estruturas de Controle**

#### ✔️ **Condicional (if / else if / else)**

```plaintext
if (<expressao>) {
    <corpo>
}
else if (<expressao>) {
    <corpo>
}
else {
    <corpo>
}
```

#### ✔️ **Repetições (loops)**

* **While:**

```plaintext
while (<expressao>) {
    <corpo>
}
```

* **Do While:**

```plaintext
do {
    <corpo>
} while (<expressao>)
```

* **For:**

```plaintext
for (<atribuicao>; <expressao>; <atribuicao>) {
    <corpo>
}
```

### 🧠 **Declaração de Funções**

```plaintext
<tipo_retorno> funcao <identificador> (<parametros>?) {
    <corpo>
}
```

Exemplo:

```plaintext
int funcao soma(int a, int b) {
    resultado = a + b
}
```

### 🔗 **Chamada de Funções**

```plaintext
<identificador>(<argumentos>?)
```

Exemplo:

```plaintext
soma(5, 10)
```

## ➕ **Expressões Aritméticas**

A linguagem suporta expressões com operadores de soma, subtração, multiplicação e divisão, além de parênteses para controle de precedência e chamadas de funções dentro das expressões.

```plaintext
<expressao> ::= <expressao_soma> (("+" | "-") <expressao_soma>)*
<expressao_soma> ::= <expressao_mult> (("*" | "/") <expressao_mult>)*
<expressao_mult> ::= <numero> | <identificador> | (<expressao>) | <chamada_funcao>
```

## 🔡 **Tipos de Dados**

* **int** → Números inteiros
* **float** → Números de ponto flutuante
* **char** → Caracteres
* **void** → Indica que uma função não possui retorno

## 🔠 **Identificadores e Números**

* **Identificadores:** Sequência de letras (ex.: `contador`, `media`).
* **Números:** Suportam inteiros, números decimais e notação científica.

  * Exemplos: `10`, `3,14`, `2e10`, `-5`, `-1,5e-3`

