%{
    /* C declarations */
    #include <stdio.h>
    #include <string.h>
    #include "setlang.tab.h"
    #include "symbol_table.h"

    void yyerror(const char *s);
%}

%option noyywrap
%option yylineno
%x COMMENT

%%

"int"   { printf("Lexer: found keyword INT\n"); return INT; }
"str"   {  return STR; }
"set"   { return SET; }
"collection"    { return COLLECTION; }
"if"    { printf("Lexer: found keyword IF\n"); return IF; }
"else"  { return ELSE; }
"while" { return WHILE; }
"for"   { return FOR; }
"input" { printf("Lexer: found keyword INPUT\n"); return INPUT; }
"output"    { printf("Lexer: found keyword OUTPUT\n"); return OUTPUT; }

"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MULTIPLY; }
"/"     { return DIVIDE; }
"&"     { return AND; }
"%"     { return MOD; }
"="     { printf("Lexer: found keyword ASSIGN\n"); return ASSIGN; }
"=="    { return EQUAL; }
"<"     { return LESS; }
">"     { return GREATER; }
"<="    { return LESS_EQUAL; }
">="    { return GREATER_EQUAL; }
"!"    { return NOT; }
"|"    { return SIZE; }

"("     { return LPAREN; }
")"     { return RPAREN; }
"["    { printf("Lexer: found keyword LBRACKET\n"); return LBRACKET; }
"]"    { printf("Lexer: found keyword RBRACKET\n"); return RBRACKET; }
"{"    {  printf("Lexer: found keyword LBRACE\n"); return LBRACE; }
"}"    { printf("Lexer: found keyword LBRACE\n"); return RBRACE; }
","    { printf("Lexer: found keyword COMMA\n"); return COMMA; }
":"    { return COLON; }
";"   { return SEMICOLON; }

[0-9]+  { printf("Lexer: found keyword INTEGER %d\n", atoi(yytext)); yylval.ival = atoi(yytext); return INTEGER; }
-?[0-9]+ { printf("Lexer: found keyword INTEGER %d\n", atoi(yytext)); yylval.ival = atoi(yytext); return INTEGER; }
\"[^\"]*\"  { printf("Lexer: found keyword STRING %s\n", yytext); yylval.sval = strdup(yytext); return STRING; }

[a-zA-Z_][a-zA-Z0-9_]* { printf("Lexer: found keyword IDENTIFIER %s\n", yytext); yylval.sval = strdup(yytext); return IDENTIFIER; }

"//".* { /* ignore single line comments */ }
"/*"   { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>.|\n { /* ignore content of multi-line comments */ }
<COMMENT><<EOF>> { yyerror("Unfinished comment"); }


[ \t\n] { /* ignore */ }

.       { printf("Unexpected character: %s\n", yytext); }

<<EOF>> { printf("Lexer: reached end of file\n"); return 0; }

%%

// noyywrap means we dont need to define yywrap()
