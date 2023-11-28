#include "parser.h"
#include <stdio.h>

static Token currentToken;

void match(TokenType expectedType) {
    if (currentToken.type == expectedType) {
        currentToken = getNextToken();
    } else {
        fprintf(stderr, "Erro de Sintaxe: esperado %s mas recebeu %s\n", getTokenTypeName(expectedType), getTokenTypeName(currentToken.type));
        currentToken = getNextToken();
    }
}

void parseVariableDeclarationList();
void parseType();
void parseCommand();
void parseAssignment();
void parseProcedureCall();
void parseConditionalCommand();
void parseRepetitiveCommand();
void parseExpression();
void parseSimpleExpression();
void parseTerm();
void parseFactor();
void parseVariable();
void parseExpressionList();

void parseProgram() {
    if (currentToken.type == PROGRAM) {
        match(PROGRAM);
        match(IDENTIFIER);
        match(SEMICOLON);
        parseBlock();
        match(DOT);
    } else {
        fprintf(stderr, "Erro de Sintaxe: esperado PROGRAM mas recebeu %s\n", getTokenTypeName(currentToken.type));
    }
}

void parseBlock() {
    if (currentToken.type == VAR) {
        parseVarDeclaration();
    }
    parseCompoundCommand();
}

void parseVarDeclaration() {
    if (currentToken.type == VAR) {
        match(VAR);
        parseVariableDeclarationList();
        match(SEMICOLON);
    }
}

void parseVariableDeclarationList() {
    parseVariable();
    while (currentToken.type == COMMA) {
        match(COMMA);
        parseVariable();
    }
    match(COLON);
    parseType();
}

void parseType() {
    if (currentToken.type == INTEGER || currentToken.type == REAL || currentToken.type == BOOLEAN) {
        currentToken = getNextToken();
    } else {
        fprintf(stderr, "Erro de Sintaxe: esperado type mas recebeu %s\n", getTokenTypeName(currentToken.type));
    }
}

void parseCompoundCommand() {
    if (currentToken.type == BEGIN) {
        match(BEGIN);
        printf("Parsing BEGIN\n");
        parseCommand();
        while (currentToken.type == SEMICOLON) {
            match(SEMICOLON);
            printf("Parsing SEMICOLON\n");
            parseCommand();
        }
        match(END);
        printf("Parsing END\n");
    } else {
        fprintf(stderr, "Erro de Sintaxe: esperado BEGIN mas recebeu %s\n", getTokenTypeName(currentToken.type));
        currentToken = getNextToken();
    }
}

void parseCommand() {
    printf("Parsing command with token: %s\n", getTokenTypeName(currentToken.type));
    if (currentToken.type == IDENTIFIER) {
        parseAssignment();
    } else if (currentToken.type == BEGIN) {
        parseCompoundCommand();
    } else if (currentToken.type == IF) {
        parseConditionalCommand();
    } else if (currentToken.type == WHILE) {
        parseRepetitiveCommand();
    } else if (currentToken.type == END_OF_FILE) {
        fprintf(stderr, "Erro de Sintaxe: inesperado token END_OF_FILE\n");
    } else {
        fprintf(stderr, "Erro de Sintaxe: inesperado token %s\n", getTokenTypeName(currentToken.type));
        currentToken = getNextToken();
    }
}

void parseAssignment() {
    printf("Parsing assignment\n");
    parseVariable();
    match(ASSIGN);
    parseExpression();
}

void parseProcedureCall() {
    if (currentToken.type == IDENTIFIER) {
        match(IDENTIFIER);
        if (currentToken.type == LPAREN) {
            match(LPAREN);
            parseExpressionList();
            match(RPAREN);
        }
    } else {
        fprintf(stderr, "Erro de Sintaxe: esperado IDENTIFIER mas recebeu %s\n", getTokenTypeName(currentToken.type));
    }
}

void parseConditionalCommand() {
    if (currentToken.type == IF) {
        match(IF);
        parseExpression();
        match(THEN);
        parseCommand();
        if (currentToken.type == ELSE) {
            match(ELSE);
            parseCommand();
        }
    } else {
        fprintf(stderr, "Erro de Sintaxe: esperado IF mas recebeu %s\n", getTokenTypeName(currentToken.type));
    }
}

void parseRepetitiveCommand() {
    if (currentToken.type == WHILE) {
        match(WHILE);
        parseExpression();
        match(DO);
        parseCommand();
    } else {
        fprintf(stderr, "Erro de Sintaxe: esperado WHILE mas recebeu %s\n", getTokenTypeName(currentToken.type));
    }
}

void parseExpression() {
    printf("Parsing expression\n");
    parseSimpleExpression();
    if (isRelationalOperator(currentToken.type)) {
        currentToken = getNextToken();
        parseSimpleExpression();
    }
}

void parseSimpleExpression() {
    if (currentToken.type == PLUS || currentToken.type == MINUS) {
        currentToken = getNextToken();
    }
    parseTerm();
    while (currentToken.type == PLUS || currentToken.type == MINUS || currentToken.type == OR) {
        currentToken = getNextToken();
        parseTerm();
    }
}

void parseTerm() {
    parseFactor();
    while (currentToken.type == TIMES || currentToken.type == DIV || currentToken.type == AND) {
        currentToken = getNextToken();
        parseFactor();
    }
}

void parseFactor() {
    if (currentToken.type == IDENTIFIER) {
        parseVariable();
    } else if (currentToken.type == NUM_INTEGER || currentToken.type == NUM_REAL) {
        currentToken = getNextToken();
    } else if (currentToken.type == LPAREN) {
        match(LPAREN);
        parseExpression();
        match(RPAREN);
    } else if (currentToken.type == NOT) {
        match(NOT);
        parseFactor();
    } else {
        fprintf(stderr, "Erro de Sintaxe: Esperado UNKNOWN mas recebeu %s\n", getTokenTypeName(currentToken.type));
        currentToken = getNextToken();
    }
}

void parseVariable() {
    match(IDENTIFIER);
}

void parseExpressionList() {
    parseExpression();
    while (currentToken.type == COMMA) {
        match(COMMA);
        parseExpression();
    }
}

void initParser(const char* input) {
    initLexer(input);
    currentToken = getNextToken();
}
