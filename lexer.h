#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LENGTH 100

typedef enum {
    PROGRAM, IDENTIFIER, SEMICOLON, DOT, VAR, INTEGER, REAL, BOOLEAN,
    PROCEDURE, LPAREN, RPAREN, COMMA, COLON, BEGIN, END, ASSIGN, IF, THEN, ELSE,
    WHILE, DO, PLUS, MINUS, OR, TIMES, DIV, AND, EQUAL, NOT_EQUAL, LESS, LESS_EQUAL,
    GREATER, GREATER_EQUAL, NUM_INTEGER, NUM_REAL, NOT, END_OF_FILE, ERROR
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[MAX_TOKEN_LENGTH];
} Token;

void initLexer(const char* input);
Token getNextToken();
const char* getTokenTypeName(TokenType type);

#endif

