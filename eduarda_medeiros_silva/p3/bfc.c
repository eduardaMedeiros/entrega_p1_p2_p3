#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// função que calcula a expressão
int calc(const char *str) {
    int total = 0;        // resultado acumulado
    int number = 0;       // número atual sendo lido
    char operation = 0;   // operador atual

    // Percorre toda a string da expressão
    while (*str) {
        if (isdigit(*str)) {
            // Constrói o número atual
            number = number * 10 + (*str - '0');
        } else if (strchr("+-*/", *str)) {
            if (operation == 0) {
                // Se ainda não há operação, o total recebe o número lido
                total = number;
            } else {
                // Caso contrário, aplica a operação anterior ao total e número atual
                switch (operation) {
                    case '+': total += number; break;
                    case '-': total -= number; break;
                    case '*': total *= number; break;
                    case '/': total /= number; break;
                }
            }
            // Atualiza o operador e reseta o número para ler o próximo
            operation = *str;
            number = 0;
        }
        str++;  // avança para o próximo caractere da string
    }

    // Aplica a última operação restante, caso exista
    if (operation != 0) {
        switch (operation) {
            case '+': total += number; break;
            case '-': total -= number; break;
            case '*': total *= number; break;
            case '/': total /= number; break;
        }
    } else {
        // Se não havia operação, o total é só o número lido
        total = number;
    }

    return total;  // retorna o resultado final da expressão
}

// Função que imprime em Brainfuck o código para zerar a célula atual e incrementar até o valor 'val', e então imprimir o caractere
void print_char(unsigned char val) {
    printf("[-]");              
    for (int i = 0; i < val; i++) 
        printf("+");            
    printf(".");                 
}

// Função que imprime uma string em Brainfuck
void print_string(const char *txt) {
    while (*txt) {
        unsigned char c = *txt;
        // Verifica se o caractere é o primeiro de um par UTF-8 (bits 110xxxxx)
        if ((c & 0xC0) == 0xC0) {
            unsigned char first = *txt++;   // pega primeiro byte do caractere
            unsigned char second = *txt++;  // pega segundo byte do caractere
            print_char(first);              
            print_char(second);              
        } else {
            print_char(*txt++);             // imprime caractere ASCII simples
        }
    }
}

// Função que converte um número inteiro em string e imprime cada dígito em Brainfuck
void print_number(int n) {
    char numstr[20];          
    sprintf(numstr, "%d", n); 
    for (int i = 0; numstr[i]; i++) {
        print_char(numstr[i]); 
    }
}

int main() {
    char buffer[1024];  
    // lê uma linha da entrada padrão, retorna erro se falhar
    if (!fgets(buffer, sizeof(buffer), stdin)) return 1;

    // procura o caractere '=' para separar parte esquerda e expressão direita
    char *equalpos = strchr(buffer, '=');
    if (!equalpos) return 1;  // erro se não encontrar '='

    *equalpos = 0;            // substitui '=' por fim de string, separando a parte esquerda
    char *left = buffer;      // parte antes do '='
    char *right = equalpos + 1; // parte depois do '='

    // remove o caractere de nova linha no final da expressão, se houver
    char *newlinepos = strchr(right, '\n');
    if (newlinepos) *newlinepos = 0;

    print_string(left);      
    print_char('=');   
    print_char(' '); 

    int val = calc(right);    // calcula a expressão
    print_number(val);        

    return 0;
}
