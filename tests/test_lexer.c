#include <stdio.h>
#include <stdlib.h>
#include "setlang.tab.h"

extern FILE* yyin;
extern char* yytext;
extern int yylex(void);

// Function to convert token numbers to names
const char* token_name(int token) {
    switch(token) {
        case INT: return "INT";
        case STR: return "STR";
        case SET: return "SET";
        case COLLECTION: return "COLLECTION";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case WHILE: return "WHILE";
        case FOR: return "FOR";
        case INPUT: return "INPUT";
        case OUTPUT: return "OUTPUT";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MULTIPLY: return "MULTIPLY";
        case DIVIDE: return "DIVIDE";
        case AND: return "AND";
        case ASSIGN: return "ASSIGN";
        case EQUAL: return "EQUAL";
        case LESS: return "LESS";
        case GREATER: return "GREATER";
        case LESS_EQUAL: return "LESS_EQUAL";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case NOT: return "NOT";
        case SIZE: return "SIZE";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LBRACKET: return "LBRACKET";
        case RBRACKET: return "RBRACKET";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case COMMA: return "COMMA";
        case SEMICOLON: return "SEMICOLON";
        case INTEGER: return "INTEGER";
        case STRING: return "STRING";
        case IDENTIFIER: return "IDENTIFIER";
        default: return "UNKNOWN";
    }
}

int main(int argc, char** argv) {
    if (argc !=2 ) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening file");
        return 1;
    }

    yyin = input;

    int token;

    while ((token = yylex()) != 0) {
        printf("Token: %-15s Lexeme: %s\n", token_name(token), yytext);
    }
    
    fclose(input);
    return 0;
}