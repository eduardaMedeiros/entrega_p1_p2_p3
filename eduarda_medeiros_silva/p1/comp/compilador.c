#include "compilador.h"

// Variáveis dos arquivos de entrada e saída
FILE* input;
FILE* output;

// Variáveis para o lexer e parser
Lexer* lexer;
Token* token;
Data* data;

// Variável para os números declarados no arquivo e quantidade
int cons[20]; 
int count_cons = 0;

// Inicializa o lexer para processar o arquivo de entrada
Lexer* create_lexer(FILE* input) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    if (!lexer) return NULL;
    
    lexer->input_file = input;
    lexer->line[0] = '\0';
    lexer->line_ptr = lexer->line;
    lexer->line_number = 0;
    
    return lexer;
}

// Cria um nó para representar um número na árvore de expressão
Node* insert_number(unsigned short value) {
    Node* node = malloc(sizeof(Node));
    if (!node) return NULL;

    node->type = NODE_NUMBER;
    node->value = value;
    return node;
}

// Cria um nó para representar uma variável na árvore de expressão
Node* insert_variable(char* variable) {
    Node* node = malloc(sizeof(Node));
    if (!node) return NULL;

    node->type = NODE_VARIABLE;
    node->variable = variable;
    return node;
}

// Cria um nó para representar uma operação (ex: +, -) na árvore de expressão
Node* insert_operation(TokenType operator, Node* left, Node* right) {
    Node* node = malloc(sizeof(Node));
    if (!node) return NULL;

    node->type = NODE_OPERATION;
    node->operation.operator = operator;
    node->operation.left = left;
    node->operation.right = right;
    return node;
}

// Insere uma nova atribuição (variável = expressão) na lista encadeada de dados
int insert_data(Data** d, char* variable, Node* expression) {
    if (*d == NULL) {
        *d = (Data*)malloc(sizeof(Data));
        if (!*d) {
            printf("Erro: Falha ao alocar memória.\n");
            return 0;
        }
        (*d)->variable = strdup(variable);
        (*d)->expression = expression;
        (*d)->prox = NULL;  
        return 1;
    }
    return insert_data(&((*d)->prox), variable, expression);
}

// Libera a memória alocada para data
void data_destroy(Data* d){
    Data* aux = d;
    while (aux != NULL) {
        Data* temp = aux;
        aux = aux->prox;
        free(temp);
    }
}

// Lê o token do lexer
char* read_token(Lexer* lexer) {
    char* token_start = lexer->line_ptr;
    
    while (*(lexer->line_ptr) && !is_delimiter(*(lexer->line_ptr))) {
        (lexer->line_ptr)++;
    }
    
    if (*(lexer->line_ptr)) {
        *(lexer->line_ptr) = '\0'; 
        (lexer->line_ptr)++; 
    }
    
    return token_start;
}

// Obtém o próximo token do lexer
void next_token(Lexer* lexer) {
    token = (Token*)malloc(sizeof(Token));
    if (!token) {
        printf("Erro: Falha ao alocar memória.\n");
    }

    token->type = NONE;
    token->value = NULL;
    token->line_number = lexer->line_number;

    while (*(lexer->line_ptr) == '\0' || *(lexer->line_ptr) == '\n') {
        if (fgets(lexer->line, MAX_LENGTH, lexer->input_file) == NULL) {
            token->type = TOKEN_EOF;
            return;
        }

        lexer->line_ptr = lexer->line;
        lexer->line_number++;
        token->line_number = lexer->line_number;
    }

    while (*(lexer->line_ptr) && is_delimiter(*(lexer->line_ptr))) {
        lexer->line_ptr++;
    }

    if (*(lexer->line_ptr) == '\0' || *(lexer->line_ptr) == '\n') {
        token->type = TOKEN_EOL;
    }

    char* token_start = read_token(lexer);
    token->type = determine_type(token_start);
    token->value = strdup(token_start);
}

// Determina o tipo do token lido
TokenType determine_type(const char* token_start) {
    if (strcmp(token_start, "PROGRAMA") == 0) {
        return PROGRAM;
    }
    else if (strcmp(token_start, "INICIO") == 0) {
        return START;
    }
    else if (strcmp(token_start, "FIM") == 0) {
        return END;
    }
    else if (isdigit(token_start[0]) || 
            (token_start[0] == '0' && (token_start[1] == 'x' || token_start[1] == 'X'))) {
        return NUMBER;
    } 
    else if (strcmp(token_start, "+") == 0) {
        return SUM;
    }
    else if (strcmp(token_start, "-") == 0) {
        return SUB;
    }
    else if (strcmp(token_start, "*") == 0) {
        return MULT;
    }
    else if (strcmp(token_start, "/") == 0) {
        return DIV;
    }
    else if ((strcmp(token_start, "RES") == 0)) {
        return RES;
    }
    else if ((strcmp(token_start, "=") == 0)) {
        return ASSIGNMENT;
    }
    else if ((strcmp(token_start, "(") == 0)) {
        return START_PAREN;
    }
    else if ((strcmp(token_start, ")") == 0) || (strcmp(token_start, ")\n") == 0)) {
        return END_PAREN;
    }
    else {
        int length = strlen(token_start);
        if (token_start[0] == '"' && token_start[length - 2] == '"') {
            for (int i = 1; i < length - 3; i++) {
                if (!isalpha(token_start[i])) {
                    return NONE;
                }
            }
            return PROGRAM_NAME;
        }

        if (isalpha(token_start[0])) {
            for (int i = 1; token_start[i] != '\0'; i++) {
                if (!isalnum(token_start[i])) {
                    return NONE; 
                }
            }
            return VARIABLE;
        }
    }
    return NONE;
}

// Libera a memória alocada para um token
void token_destroy(Token* token) {
    if (token) {
        if (token->value) {
            free(token->value);
        }
        free(token);
    }
}

// Converte um número em string para um valor inteiro
int parse_number(const char* str) {
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        return strtol(str + 2, NULL, 16); 
    }
    return atoi(str); 
}

// Verifica se um caractere é um delimitador
int is_delimiter(char c) {
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

// Lê o arquivo de entrada e processa seus tokens
int read_file(Lexer* lexer) {
    next_token(lexer);

    if (token->type != PROGRAM) {
        printf("Erro: PROGRAMA esperado na linha %d\n", token->line_number);
        token_destroy(token);
        return 0;
    }

    next_token(lexer);
    if (token->type != PROGRAM_NAME) {
        printf("Erro: Nome do programa esperado depois de PROGRAMA na linha: %d\n", token->line_number);
        token_destroy(token);
        return 0;
    }

    int length = strlen(token->value);
    if (token->value[length - 1] != ':') {
        printf("Erro: ':' esperado depois do nome do programa na linha: %d\n", token->line_number);
        token_destroy(token);
        return 0;
    }

    next_token(lexer);
    if (token->type != START) {
        printf("Erro: INICIO esperado na linha: %d\n", token->line_number);
        token_destroy(token);
        return 0;
    }

    int expre = 1;
    int result = 1;

    next_token(lexer);
    while (expre) {
        if(token->type != RES && token->type != TOKEN_EOF){
            if(!parse_assignment(lexer)){
                result = 0;
                return result;
            }
            
        }else {
            expre = 0;
        }

    }

    if(result){
        if (token->type != RES) {
            printf("Erro: RES esperado na linha: %d\n", token->line_number);
            token_destroy(token);
            return 0;
        }
    
        char* variable = token->value;
    
        next_token(lexer);
        if (token->type != ASSIGNMENT) {
            printf("Erro: '=' esperado após RES na linha: %d\n", token->line_number);
            token_destroy(token);
            return 0;
        }
    
        Node* expression = parse_expression(lexer); 
    
        if(expression != NULL){
            if(!insert_data(&data, variable, expression)) {
                printf("Erro: Falha ao inserir dados na lista\n");
                return 0;
            }
        }
    
        if (token->type != END) {
            printf("Erro: FIM esperado na linha: %d\n", token->line_number);
            token_destroy(token);
            return 0;
        }
    }
    
    token_destroy(token);
    return 1;
}

// Analisa uma instrução de atribuição (ex: x = 2 + y) e a adiciona à lista de dados
int parse_assignment(Lexer* lexer) {
    if (token->type != VARIABLE && token->type != RES) {
        printf("Erro: Nome Válido da Variável esperada na linha: %d\n", token->line_number);
        token_destroy(token);
        return 0;
    }

    char* variable = token->value;

    next_token(lexer);
    if (token->type != ASSIGNMENT) {
        printf("Erro: '=' esperado após Nome da Variável na linha: %d\n", token->line_number);
        token_destroy(token);
        return 0;
    }

    Node* expression = parse_expression(lexer); 

    if(expression != NULL){
        if(!insert_data(&data, variable, expression)) {
            printf("Erro: Falha ao inserir dados na lista\n");
            return 0;
        }
    }else{
        return 0;
    }

    return 1;
}

// Analisa uma expressão com operadores de soma e subtração
Node* parse_expression(Lexer* lexer) {
    next_token(lexer);
    Node* node = parse_term(lexer);
    if (node != NULL) {
        while (token->type == SUM || token->type == SUB) {
            TokenType operator = token->type;
            next_token(lexer);
            Node* right = parse_term(lexer);
            node = insert_operation(operator, node, right);
        }
    }
    return node;
}

// Analisa termos com operadores de multiplicação e divisão
Node* parse_term(Lexer* lexer) {
    Node* node = parse_factor(lexer);
    if (node != NULL) {
        while (token->type  == MULT || token->type  == DIV) {
            TokenType operator = token->type;
            next_token(lexer);
            Node* right = parse_factor(lexer);
            node = insert_operation(operator, node, right);
        }
    }
    return node;
}

// Analisa fatores que podem ser números, variáveis ou expressões entre parênteses
Node* parse_factor(Lexer* lexer) {
    if (token->type == NUMBER) {
        Node* node = insert_number(parse_number(token->value));
        
        int length = strlen(token->value);
        if(!(token->value[length - 1] == '\n')){
            next_token(lexer);
        }
        return node;
    }else if (token->type == VARIABLE) {
        Node* node = insert_variable(token->value);
            
        int length = strlen(token->value);
        if(!(token->value[length - 1] == '\n')){
            next_token(lexer);
        }
        return node;
    } else if (token->type == START_PAREN) {
        Node* node = parse_expression(lexer);
        if (token->type != END_PAREN) {
            printf("Erro: ')' esperado após expressão na linha: %d\n", token->line_number);
            return NULL;
        }
        next_token(lexer);
        return node;
    } else {
        printf("Erro sintático: Fator inválido na linha: %d\n", token->line_number);
        return NULL;
    }
}

// função recursiva que gera o código de uma expressão
void generate_expression(FILE* output, Node* expr) {
    if (expr->type == NODE_NUMBER) {
        fprintf(output, "LDA C%d\n", expr->value);
    } else if (expr->type == NODE_VARIABLE) {
        fprintf(output, "LDA %s\n", expr->variable);
    } else if (expr->type == NODE_OPERATION) {
        Node* left = expr->operation.left;
        Node* right = expr->operation.right;
        TokenType op = expr->operation.operator;

        generate_expression(output, left);
        fprintf(output, "STA TMP\n");

        generate_expression(output, right);
        fprintf(output, "STA TMP2\n");

        if (op == SUM) {
            fprintf(output, "LDA TMP\n");
            fprintf(output, "ADD TMP2\n");
        } else if (op == SUB) {
            fprintf(output, "LDA TMP2\n");
            fprintf(output, "NOT\n");
            fprintf(output, "ADD C1\n");
            fprintf(output, "ADD TMP\n");
        }
    }
}

int is_new_cons(int value) {
    for (int i = 0; i < count_cons; i++) {
        if (cons[i] == value)
            return 0;
    }
    cons[count_cons++] = value;
    return 1;
}

void generate_const(FILE* output, Node* expr) {
    if (expr->type == NODE_NUMBER) {
        if(is_new_cons(expr->value))
            fprintf(output, "C%d DB %d\n", expr->value, expr->value);
    } else if (expr->type == NODE_OPERATION) {
        Node* left = expr->operation.left;
        Node* right = expr->operation.right;
      
        generate_const(output, left);
    
        if (right->type == NODE_NUMBER) {
            if(is_new_cons(right->value))
                fprintf(output, "C%d DB %d\n", right->value, right->value);
        } else if (right->type == NODE_OPERATION) {
            generate_const(output, right);
        }
    }
}

void create_file(const char* filename, Data* data) {
    FILE* output = fopen(filename, "w");
    if (!output) {
        printf("Erro ao criar arquivo %s\n", filename);
        return;
    }

    // .DATA 
    fprintf(output, ".DATA\n");
    fprintf(output, "TMP DB ?\n");
    fprintf(output, "TMP2 DB ?\n");

    fprintf(output, "C1 DB 1\n");
    cons[0] = 1;
    count_cons = 1;

    for (Data* d = data; d != NULL; d = d->prox) {
        fprintf(output, "%s DB ?\n", d->variable);
        generate_const(output, d->expression);
    }

    // .CODE
    fprintf(output, "\n.CODE\n.ORG 0\n");

    for (Data* d = data; d != NULL; d = d->prox) {
        generate_expression(output, d->expression);
        fprintf(output, "STA %s\n", d->variable);
    }

    fprintf(output, "HLT\n");
    fclose(output);
}

// função principal que inicializa o lexer e parser, lê o arquivo e gera o .asm
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Número de parâmetros diferente do esperado. Use ./<program> programa.lpn\n");
        return 0;
    }

    input = fopen(argv[1], "r");
    if (!input) {
        printf("Não foi possível abrir o arquivo .lpn\n");
        return 0;
    }

    lexer = create_lexer(input);
    if (!lexer) {
        printf("Falha ao iniciar lexer\n");
        fclose(input);
        return 0;
    }

    data = NULL;
    if (!read_file(lexer)) {
        free(lexer);
        data_destroy(data);
        fclose(input);
        return 0;
    }

    create_file("programa.asm", data);
    printf("Arquivo assembly gerado corretamente: programa.asm\n");

    data_destroy(data);
    free(lexer);
    fclose(input);
    return 0;
}