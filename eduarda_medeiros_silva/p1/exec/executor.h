#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define OFFSET 2

#define NOP 0
#define STA 16
#define LDA 32
#define ADD 48
#define OR 64
#define AND 80
#define NOT 96
#define JMP 128
#define JN 144
#define JZ 160
#define HLT 240

void flags();
void print();
int read(uint16_t cmd);

#endif