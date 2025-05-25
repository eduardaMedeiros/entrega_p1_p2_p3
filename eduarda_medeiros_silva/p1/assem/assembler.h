#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MEMORY_SIZE 512 
#define MAX_LENGTH 256

// definições de Tipos
typedef enum {
    NONE,
    MNEMONIC,
    NUMBER,
    DIRECTIVE,
    VARIABLE_TYPE,
    VARIABLE,
    TOKEN_EOL,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char* value;
    int line_number;
} Token;

typedef struct {
    FILE* input_file;
    char line[MAX_LENGTH];
    char* line_ptr;
    int line_number;
    int in_comment;
} Lexer;

typedef struct {
    char* mnemonic;
    unsigned short opcode; 
} Instruction;

typedef struct Data {
    char* variable;
    char* variable_type;
    int variable_address;
    unsigned short value;
    struct Data* prox;
} Data;

typedef struct {
    Lexer* lexer;
    Data* data;
    unsigned short memory[MEMORY_SIZE];
    int org;
    int code_address;
    int max_address;
    int in_data_section;
    int in_org_section;
    const Instruction* instructions;
    int num_instructions;
} Parser;

// funções para manipulação do Data
int insert_data(Data** d, char* variable, char* variable_type, int variable_address, unsigned short value);
Data* search_data(Data* d, char* variable);
void data_destroy(Data* d);

// funções do Lexer
Lexer* create_lexer(FILE* input);
char* read_token(Lexer* lexer);
Token* next_token(Lexer* lexer);
void token_destroy(Token* token);

// funções do Parser
Parser* create_parser(Lexer* lexer, Data* data);
int parse_number(const char* str);
int read_file(Parser* parser);
int read_data(Parser* parser, Token* token);
int read_code(Parser* parser, Token* token);
int read_org(Parser* parser, Token* token);

// utilitários e Busca
int find_instruction(const Instruction* instructions, int num_instructions, const char* mnemonic);
TokenType determine_type(const char* token_start);
void count_instructions(Parser* parser);
void addressing_data(Parser* parser);
int is_delimiter(char c);
int is_comment(const char* line);

#endif
