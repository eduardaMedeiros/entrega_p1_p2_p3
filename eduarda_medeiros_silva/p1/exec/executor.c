#include "executor.h"

FILE *file;
uint16_t memory[258];

uint8_t pc = 0;
int8_t ac = 0;

int n = 0;
int z = 0;

void flags() {
  n = (ac & 0x80) != 0;   
  z = (ac == 0);        
}

int read(uint16_t cmd) {
    switch (cmd) {
    case NOP:
        pc++;
        break;

    case STA:
        memory[memory[pc + OFFSET + 1] + OFFSET] = ac;
        pc += 2;
        break;

    case LDA:
        ac = memory[memory[pc + OFFSET + 1] + OFFSET];
        pc += 2;
        flags();
        break;

    case ADD:
        ac += memory[memory[pc + OFFSET + 1] + OFFSET];
        pc += 2;
        flags();
        break;

    case OR:
        ac |= memory[memory[pc + OFFSET + 1] + OFFSET];
        pc += 2;
        flags();
        break;

    case AND:
        ac &= memory[memory[pc + OFFSET + 1] + OFFSET];
        pc += 2;
        flags();
        break;

    case NOT:
        ac = ~ac;
        pc += 1;
        flags();
        break;

    case JMP:
        pc = memory[pc + OFFSET + 1];
        break;

    case JN:
        if (n) {
            pc = memory[pc + OFFSET + 1];
        } else {
            pc += 2;
        }
        break;

    case JZ:
        if (z) {
            pc = memory[pc + OFFSET + 1];
        } else {
            pc += 2;
        }
        break;

    case HLT:
        return 0;

    default:
        printf("Comando não reconhecido: %d\n", cmd);
        return 0;
    }

    return 1;
}


void print() {
    printf("----------------------------\n");
    printf("|  PC  |  AC  |  N  |  Z  |\n");
    printf("|------|------|-----|-----|\n");
    printf("| %4d | %4d |  %d  |  %d  |\n", pc, ac, n, z);
    printf("----------------------------\n");

    printf("\nMemória:\n");
    for (int i = 2; i < 258; i++) {
        printf("[%3d] %4d\n", i - 2, memory[i]);
    }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Quantidade de parâmetros inválida");
    return 1;
  }

  file = fopen(argv[1], "rb");
  if (file == NULL) {
    printf("Não foi encontrado o arquivo informado.\n");
    return 1;
  }

  size_t items = fread(memory, 2, 258, file);
  if (items != 258) {
    printf("Erro ao ler o arquivo.\n");
    fclose(file);
    return 1;
  }

  fclose(file);

  int start = 1;
  while (start) {
    start = read(memory[pc + OFFSET]);
  }
  print();

  FILE *arquivo = fopen("export.mem", "wb");
  if (arquivo == NULL) {
    printf("Erro ao criar arquivo para exportação");
    return 1;
  }

  fwrite(memory, 2, 258, arquivo);
  fclose(arquivo);

  return 0;
}