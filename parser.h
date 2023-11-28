#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

void initParser(const char* input);
void parseProgram();
void parseBlock();
void parseVarDeclaration();
void parseVarList();
void parseType();
void parseProcedureDeclaration();
void parseFormalParameters();
void parseFormalParameterSection();
void parseCommand();
void parseCompoundCommand();
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
const char* getTokenTypeName(TokenType type);

#endif

