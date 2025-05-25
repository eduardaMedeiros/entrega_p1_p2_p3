#ifndef COMPILADOR_H
#define COMPILADORR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 256

// definições de tipos
typedef enum {
    NONE,
    PROGRAM,
    PROGRAM_NAME,
    START,
    END,
    VARIABLE,
    RES,
    ASSIGNMENT,
    NUMBER,
    SUM,
    SUB,
    MULT,
    DIV,
    START_PAREN,
    END_PAREN,
    TOKEN_EOL,
    TOKEN_EOF
} TokenType;

typedef enum {
    NODE_NUMBER,
    NODE_VARIABLE,
    NODE_OPERATION
} NodeType;

typedef struct Token {
    TokenType type;
    char* value;
    int line_number;
} Token;

typedef struct Lexer {
    FILE* input_file;
    char line[MAX_LENGTH];
    char* line_ptr;
    int line_number;
} Lexer;

typedef struct Node {
    NodeType type;
    union {
        char* variable;
        unsigned short value; 
        struct {
            TokenType operator;
            struct Node* left;
            struct Node* right;
        } operation;
    };
} Node;

typedef struct Data {
    char* variable;
    Node* expression;
    struct Data* prox;
} Data;

// funções para manipulação do data
Node* insert_number(unsigned short value);
Node* insert_variable(char* variable);
Node* insert_operation(TokenType operator, Node* left, Node* right);

int insert_data(Data** d, char* variable, Node* expression);
void data_destroy(Data* d);

// funções do lexer
Lexer* create_lexer(FILE* input);
char* read_token(Lexer* lexer);
void next_token(Lexer* lexer);
void token_destroy(Token* token);

// funções do parser
int parse_number(const char* str);
int parse_assignment(Lexer* lexer);
Node* parse_expression(Lexer* lexer);
Node* parse_term(Lexer* lexer);
Node* parse_factor(Lexer* lexer);
int read_file(Lexer* lexer);

// utilitários e busca
TokenType determine_type(const char* token_start);
int is_delimiter(char c);

//criação do arquivo .asm
void create_file(const char* filename, Data* data);
int is_new_cons(int value);
void generate_const(FILE* output, Node* expr);
void generate_expression(FILE* output, Node* expr);

#endif
