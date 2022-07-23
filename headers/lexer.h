#ifndef _LEXER_H
#define _LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define LIST_SIZE 10

enum TokenType {
    PLUS, MINUS, STAR, SLASH, MODULO, DECR, INCR, LEFT_SHIFT, RIGHT_SHIFT,
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, 
    LEFT_BRACKET, RIGHT_BRACKET, 
    SEMICOLON, COMMA, DOT,
    QMARK, COLON,

    EQUAL, EQUAL_EQUAL, BANG, BANG_EQUAL, LESS, LESS_EQUAL,
    GREATER, GREATER_EQUAL, AND, OR, BIT_AND, BIT_OR, XOR, BIT_NOT,
    PLUS_EQUAL, MINUS_EQUAL, STAR_EQUAL, SLASH_EQUAL, MODULO_EQUAL,

    CONST, INT, DOUBLE, FLOAT, CHAR, UNSIGNED, LONG,
    ENUM, STRUCT, UNION, TYPEDEF, IDENTIFIER,
    
    STRING, NUMBER, TRUE, FALSE, NIL,

    RETURN, DO, WHILE, FOR, IF, ELSE, 

    PREPROC,

    WHITE_SPACE, TAB_SPACE, CARR_SPACE, NEW_LINE,

    ENDFILE
};

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

typedef struct {
    enum TokenType type;
    char* lexeme;
    Color c;
} Token;

typedef struct {
    Token* tokens;
    size_t index;
    size_t max;
} TokenList;



#define HASH_SIZE 100
typedef struct nlist Hashlist;
struct nlist{
    struct nlist* next;
    char* key;
    enum TokenType val;
};


void initTokenList(TokenList* list);
TokenList* tokenize(char* input);

#endif //_LEXER_H
