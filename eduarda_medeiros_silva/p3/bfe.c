#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 30000  // tamanho da fita de memória

int main() {
    char prog[65536];          // buffer para código Brainfuck
    char mem[MEM_SIZE] = {0};  // fita de memória zerada
    int memPtr = 0;            // ponteiro da fita
    int instrPtr = 0;          // índice do comando atual
    int progLen = 0;           // tamanho do programa

    // lê o programa até EOF ou limite do buffer
    while ((prog[progLen] = getchar()) != EOF && progLen < 65535) progLen++;
    prog[progLen] = '\0';

    // executa o programa
    while (instrPtr < progLen) {
        char cmd = prog[instrPtr];

        switch (cmd) {
            case '>': memPtr++; break;         // avança ponteiro da fita
            case '<': memPtr--; break;         // retrocede ponteiro da fita
            case '+': mem[memPtr]++; break;    // incrementa célula atual
            case '-': mem[memPtr]--; break;    // decrementa célula atual
            case '.': putchar(mem[memPtr]); break;  // imprime caractere
            case ',': mem[memPtr] = getchar(); break; // lê caractere
            case '[':
                if (mem[memPtr] == 0) {       // pula loop se célulafor igual a zero
                    int depth = 1;
                    while (depth > 0) {
                        instrPtr++;
                        if (prog[instrPtr] == '[') depth++;
                        else if (prog[instrPtr] == ']') depth--;
                    }
                }
                break;
            case ']':
                if (mem[memPtr] != 0) {       // volta para '[' se célula não for zero
                    int depth = 1;
                    while (depth > 0) {
                        instrPtr--;
                        if (prog[instrPtr] == '[') depth--;
                        else if (prog[instrPtr] == ']') depth++;
                    }
                }
                break;
        }

        instrPtr++; // próximo comando
    }

    return 0;
}
