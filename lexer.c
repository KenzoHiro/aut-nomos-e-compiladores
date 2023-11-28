#include "lexer.h"
#include <ctype.h>
#include <string.h>

static const char* input;
static int currentPosition;

void initLexer(const char* inputString) {
    input = inputString;
    currentPosition = 0;
}

static char peek() {
    return input[currentPosition];
}

static void advance() {
    currentPosition++;
}

static void skipWhitespace() {
    while (isspace(peek())) {
        advance();
    }
}

const char* getTokenTypeName(TokenType type) {
    switch (type) {
        case PROGRAM:
            return "PROGRAM";
        case VAR:
            return "VAR";
        case BEGIN:
            return "BEGIN";
        case END:
            return "END";
        case INTEGER:
            return "INTEGER";
        case REAL:
            return "REAL";
        case BOOLEAN:
            return "BOOLEAN";
        case PROCEDURE:
            return "PROCEDURE";
        case IDENTIFIER:
            return "IDENTIFIER";
        case SEMICOLON:
            return "SEMICOLON";
        case COLON:
            return "COLON";
        case COMMA:
            return "COMMA";
        case ASSIGN:
            return "ASSIGN";
        case EQUAL:
            return "EQUAL";
        case NOT_EQUAL:
            return "NOT_EQUAL";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case TIMES:
            return "TIMES";
        case DIV:
            return "DIV";
        case AND:
            return "AND";
        case OR:
            return "OR";
        case NOT:
            return "NOT";
        case LPAREN:
            return "LPAREN";
        case RPAREN:
            return "RPAREN";
        case IF:
            return "IF";
        case THEN:
            return "THEN";
        case ELSE:
            return "ELSE";
        case WHILE:
            return "WHILE";
        case DO:
            return "DO";
        case NUM_INTEGER:
            return "NUM_INTEGER";
        case NUM_REAL:
            return "NUM_REAL";
        case END_OF_FILE:
            return "END_OF_FILE";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

static Token createToken(TokenType type, const char* lexeme) {
    Token token;
    token.type = type;
    strncpy(token.lexeme, lexeme, MAX_TOKEN_LENGTH);
    token.lexeme[MAX_TOKEN_LENGTH - 1] = '\0'; 
    return token;
}

static Token scanIdentifierOrKeyword() {
    char lexeme[MAX_TOKEN_LENGTH];
    int i = 0;
    while (isalnum(peek()) || peek() == '_') {
        lexeme[i++] = peek();
        advance();
    }
    lexeme[i] = '\0';

    if (strcmp(lexeme, "program") == 0) {
        return createToken(PROGRAM, lexeme);
    } else {
        return createToken(IDENTIFIER, lexeme);
    }
}

static Token scanOperator() {
    char lexeme[MAX_TOKEN_LENGTH];
    int i = 0;
    while (strchr("+-*/=<>", peek()) != NULL) {
        lexeme[i++] = peek();
        advance();
    }
    lexeme[i] = '\0';
    if (strcmp(lexeme, "+") == 0) return createToken(PLUS, lexeme);
    else if (strcmp(lexeme, "-") == 0) return createToken(MINUS, lexeme);
    else if (strcmp(lexeme, "*") == 0) return createToken(TIMES, lexeme);
    else if (strcmp(lexeme, "/") == 0) return createToken(DIV, lexeme);
    else if (strcmp(lexeme, "=") == 0) return createToken(EQUAL, lexeme);
    else if (strcmp(lexeme, "<") == 0) return createToken(LESS, lexeme);
    else if (strcmp(lexeme, ">") == 0) return createToken(GREATER, lexeme);
    else return createToken(ERROR, lexeme);
}

static Token scanNumber() {
    char lexeme[MAX_TOKEN_LENGTH];
    int i = 0;
    while (isdigit(peek())) {
        lexeme[i++] = peek();
        advance();
    }
    lexeme[i] = '\0';
    return createToken(NUM_INTEGER, lexeme);
}

Token getNextToken() {
    skipWhitespace();
    if (peek() == '\0') {
        return createToken(END_OF_FILE, "");
    }
    switch (peek()) {
        case '.':
            advance();
            return createToken(DOT, ".");
        case ';':
            advance();
            return createToken(SEMICOLON, ";");
        case ',':
            advance();
            return createToken(COMMA, ",");
        case ':':
            advance();
            return createToken(COLON, ":");
        case '(':
            advance();
            return createToken(LPAREN, "(");
        case ')':
            advance();
            return createToken(RPAREN, ")");
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
        case '<':
        case '>':
            return scanOperator();
        default:
            if (isalpha(peek()) || peek() == '_') {
                return scanIdentifierOrKeyword();
            } else if (isdigit(peek())) {
                return scanNumber();
            } else {
                char lexeme[2] = {peek(), '\0'};
                advance();
                return createToken(ERROR, lexeme);
            }
    }
}

int isRelationalOperator(TokenType type) {
    switch (type) {
        case EQUAL:
        case NOT_EQUAL:
        case LESS:
        case GREATER:
            return 1;  // É um operador relacional
        default:
            return 0;  // Não é um operador relacional
    }
}
