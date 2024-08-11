%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "symbol_table.h"

    extern int yylex();
    extern int yylineno;
    extern char* yytext;
    void yyerror(const char *s);
    FILE* yyin;
    FILE* yyout;

    void yyerror(const char* s);
    int yydebug = 1; //enable debugging

    SymbolType current_type;

    //Function to generate unique labels
    int label_count = 0;
    char* new_label() {
        char* label = malloc(20);
        snprintf(label, 20, "L%d", label_count++);
        return label;
    }

    //function to check if an expression is a string
    int is_string(const char* expr) {
        return expr[0] == '"' && expr[strlen(expr) - 1] == '"';
    }

    //function to get expression type
    SymbolType get_expression_type(const char* expr) {
        if (strncmp(expr, "set_", 4) == 0) {
            return TYPE_SET;
        } else if (strncmp(expr, "collection_", 11) == 0) {
            return TYPE_COLLECTION;
        } else if (expr[0] >= '0' && expr[0] <= '9') {
            return TYPE_INT;
        } else {
            Symbol* sym = lookup_symbol(expr);
            if (sym != NULL) {
                return sym->type;
            }
        }
        return TYPE_INT;
    }
%}

%union {
    int ival;
    char *sval;
    char *code;
}

%token <ival> INTEGER
%token <sval> STRING IDENTIFIER

%token INT STR SET COLLECTION
%token IF ELSE WHILE FOR
%token INPUT OUTPUT
%token LBRACKET RBRACKET LBRACE RBRACE LPAREN RPAREN
%token COMMA SIZE SEMICOLON COLON
%token PLUS MINUS MULTIPLY DIVIDE AND ASSIGN EQUAL LESS GREATER LESS_EQUAL GREATER_EQUAL NOT

%type <code> expression statement statement_list declaration assignment if_statement while_statement for_statement input_statement output_statement
%type <code> set_expression collection_expression element_list condition
%type <code> identifier_list
%type <code> expression_list
%type <code> set_or_collection
%type <code> output_list output_item

%left AND
%left EQUAL LESS GREATER LESS_EQUAL GREATER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE
%right NOT
%left SIZE

%%

program: statement_list { 
        printf("Completed parsing program\n");
        fprintf(yyout, "%s", $1);
    }   
    ;

statement_list: statement { $$ = $1;}
                | statement_list statement {
                    $$ = malloc(strlen($1) + strlen($2) + 2);
                    sprintf($$, "%s\n%s", $1, $2);
                    free($1);
                    free($2);
                }
                ;

statement: declaration { $$ = $1; }
            | assignment { $$ = $1; }
            | if_statement { $$ = $1; }
            | while_statement { $$ = $1; }
            | for_statement { $$ = $1; }
            | input_statement { $$ = $1; }
            | output_statement { $$ = $1; }
            | LBRACE statement_list RBRACE
            | expression SEMICOLON {
                $$ = malloc(strlen($1) + 3);
                sprintf($$, "%s;", $1);
                free($1);
            }
            ;

declaration: INT { current_type = TYPE_INT; } identifier_list SEMICOLON {
                printf("Declaring INT: %s\n", $3);  // Debug print
                $$ = malloc(strlen($3) + 7);
                sprintf($$, "int %s;", $3);
                free($3);
            }
            | STR { current_type = TYPE_STR; } identifier_list SEMICOLON {
                printf("Declaring STR: %s\n", $3);  // Debug print
                $$ = malloc(strlen($3) + 15);
                sprintf($$, "char* %s = NULL;", $3);
                free($3);
            }
            | SET { current_type = TYPE_SET; } identifier_list SEMICOLON {
                printf("Declaring SET: %s\n", $3);  // Debug print
                char* temp = strdup($3);
                char* token = strtok(temp, ",");
                $$ = malloc(1);
                $$[0] = '\0';
                while (token != NULL) {
                    char* trimmed = token;
                    while (*trimmed == ' ') trimmed++; // trim leading spaces
                    char* end = trimmed + strlen(trimmed) - 1;
                    while (end > trimmed && *end == ' ') end--; // trim trailing spaces
                    *(end + 1) = '\0';

                    char* new_decl = malloc(strlen(trimmed) + 30);
                    sprintf(new_decl, "set_t* %s = set_new();\n", trimmed);

                    $$ = realloc($$, strlen($$) + strlen(new_decl) + 1);
                    strcat($$, new_decl);

                    free(new_decl);
                    token = strtok(NULL, ",");
                }
                free(temp);
                free($3);
            }
            | COLLECTION { current_type = TYPE_COLLECTION; } identifier_list SEMICOLON {
                printf("Declaring COLLECTION: %s\n", $3);  // Debug print
                char* temp = strdup($3);
                char* token = strtok(temp, ",");
                $$ = malloc(1);
                $$[0] = '\0';
                while (token != NULL) {
                    char* trimmed = token;
                    while (*trimmed == ' ') trimmed++; // trim leading spaces
                    char* end = trimmed + strlen(trimmed) - 1;
                    while (end > trimmed && *end == ' ') end--; // trim trailing spaces
                    *(end + 1) = '\0';

                    char* new_decl = malloc(strlen(trimmed) + 30);
                    sprintf(new_decl, "collection_t* %s = collection_new();\n", trimmed);

                    $$ = realloc($$, strlen($$) + strlen(new_decl) + 1);
                    strcat($$, new_decl);

                    free(new_decl);
                    token = strtok(NULL, ",");
                }
                free(temp);
                free($3);
            }
            ;

identifier_list: IDENTIFIER {
                    if (!insert_symbol($1, current_type)) {
                        yyerror("Symbol already defined");
                    }
                    $$ = strdup($1);
                }
                | identifier_list COMMA IDENTIFIER {
                    if (!insert_symbol($3, current_type)) {
                        yyerror("Symbol already defined");
                    }
                    $$ = malloc(strlen($1) + strlen($3) + 3);
                    sprintf($$, "%s, %s", $1, $3);
                    free($1);
                }
            ;

assignment: IDENTIFIER ASSIGN expression SEMICOLON {
                printf("Debug: Assigning to: %s\n", $1);  // Debug print
                printf("Expression: %s\n", $3);  // Debug print
                Symbol* sym = lookup_symbol($1);
                if (sym == NULL) {
                    yyerror("Undefined variable");
                } else {
                    SymbolType type = get_expression_type($3);
                    if(strncmp($3, "set_add", 7) == 0 || strncmp($3, "set_remove", 10) == 0) {
                        // for set_add and set_remove, dont assign result
                        $$ = malloc(strlen($3) + 2);
                        sprintf($$, "%s;", $3);
                    } else if (sym->type == TYPE_SET && type == TYPE_SET) {
                        $$ = malloc(strlen($1) + strlen($3) + 50);
                        sprintf($$, "set_free(%s);\n%s = %s;", $1, $1, $3);
                    } else {
                        $$ = malloc(strlen($1) + strlen($3) + 5);
                        sprintf($$, "%s = %s;", $1, $3);
                    }
                }
                free($1);
                free($3);
            }
            ;

if_statement: IF LPAREN condition RPAREN statement {
                char* label = new_label();
                $$ = malloc(strlen($3) + strlen($5) + strlen(label) + 50);
                sprintf($$, "if (!(%s)) goto %s;\n%s\n%s:", $3, label, $5, label);
                free($3);
                free($5);
                free(label);
            }
            | IF LPAREN condition RPAREN statement ELSE statement {
                char* else_label = new_label();
                char* end_label = new_label();
                $$ = malloc(strlen($3) + strlen($5) + strlen($7) + strlen(else_label) + strlen(end_label) + 100);
                sprintf($$, "if (!(%s)) goto %s;\n%s\ngoto %s;\n%s:\n%s\n%s",
                        $3, else_label, $5, end_label, else_label, $7, end_label);
                free($3);
                free($5);
                free($7);
                free(else_label);
                free(end_label);
            }
            | IF LPAREN condition RPAREN LBRACE statement_list RBRACE {
                char* label = new_label();
                $$ = malloc(strlen($3) + strlen($6) + strlen(label) + 50);
                sprintf($$, "if (!(%s)) goto %s;\n{\n%s\n}\n%s:", $3, label, $6, label);
                free($3);
                free($6);
                free(label);
            }
            | IF LPAREN condition RPAREN LBRACE statement_list RBRACE ELSE LBRACE statement_list RBRACE {
                char *else_label = new_label();
                char *end_label = new_label();
                $$ = malloc(strlen($3) + strlen($6) + strlen($10) + strlen(else_label) + strlen(end_label) + 100);
                sprintf($$, "if (!(%s)) goto %s;\n{\n%s\n}\ngoto %s;\n%s:\n{\n%s\n}\n%s:", 
                        $3, else_label, $6, end_label, else_label, $10, end_label);
                free($3);
                free($6);
                free($10);
                free(else_label);
                free(end_label);
            }
            ;

while_statement: WHILE LPAREN condition RPAREN statement {
                    char* start_label = new_label();
                    char* end_label = new_label();
                    $$ = malloc(strlen($3) + strlen($5) + strlen(start_label) + strlen(end_label) + 100);
                    sprintf($$, "%s:\nif (!%s) goto %s;\n%s\ngoto %s;\n%s:", 
                            start_label, $3, end_label, $5, start_label, end_label);
                    free($3);
                    free($5);
                    free(start_label);
                    free(end_label);
                }
                ;

for_statement: FOR LPAREN IDENTIFIER COLON set_or_collection RPAREN statement {
                    char* start_label = new_label();
                    char* end_label = new_label();
                    $$ = malloc(strlen($3) + strlen($5) + strlen($7) + strlen(start_label) + strlen(end_label) + 200);
                    sprintf($$, "{\n iterator_t it = iterator_new(%s);\n"
                                " %s:\n"
                                " if (!iterator_has_next(&it)) goto %s;\n"
                                " %s = iterator_next(&it);\n"
                                " %s\n"
                                " goto %s;\n"
                                " %s:\n"
                                " iterator_free(&it);\n"
                                "}\n",
                            $5, start_label, end_label, $3, $7, start_label, end_label);
                    free($5);
                    free($7);
                    free(start_label);
                    free(end_label);
                }
                ;

input_statement: INPUT expression IDENTIFIER SEMICOLON {
                Symbol* sym = lookup_symbol($3);
                if (sym == NULL) {
                    yyerror("Undefined variable");
                }
                $$ = malloc(strlen($2) + strlen($3) + 100);
                sprintf($$, "printf(%s);\n"
                            "if (scanf(\"%%d\", &%s) != 1) {\n"
                            "   fprintf(stderr, \"Invalid input\\n\");\n"
                            "   exit(1);\n"
                            "}\n", $2, $3);
                free($2);
                }
                ;

output_statement: OUTPUT output_list SEMICOLON {
                    $$ = malloc(strlen($2) + 100);
                    strcpy($$, "");
                    char *token = strtok($2, ";");
                    while (token != NULL) {
                        char *temp = malloc(strlen(token) + 100);
                        if (token[0] == '"') { // String literal
                            sprintf(temp, "printf(%s);\n", token);
                        } else if (strstr(token, "set_size") != NULL) { // Set size
                            char *set_name = strdup(token + 9); // skip "set_size("
                            set_name[strlen(set_name) - 1] = '\0'; // remove trailing ')'
                            sprintf(temp, "printf(\"%%d\", set_size(%s));\n", set_name);
                            free(set_name);
                        } else {
                            Symbol *sym = lookup_symbol(token);
                            if (sym == NULL) {
                                yyerror("Undefined variable");
                            } else if (sym->type == TYPE_INT) {
                                sprintf(temp, "printf(\"%%d\", %s);\n", token);
                            } else if (sym->type == TYPE_SET) {
                                sprintf(temp, "set_print(%s);\n", token);
                            } else if (sym->type == TYPE_COLLECTION) {
                                sprintf(temp, "collection_print(%s);\n", token);
                            } else {
                                yyerror("Unsupported type for output");
                            }
                        }
                        strcat($$, temp);
                        free(temp);
                        token = strtok(NULL, ";");
                    }
                    strcat($$, "printf(\"\\n\");\n");
                    free($2);
                }
                ;

output_list: output_item { $$ = $1; }
        | output_list output_item {
            $$ = malloc(strlen($1) + strlen($2) + 2);
            sprintf($$, "%s;%s", $1, $2);
            free($1);
            free($2);
        }
        ;

output_item: expression {
                if (is_string($1)) {
                    $$ = $1;
                } else {
                    Symbol *sym = lookup_symbol($1);
                    if (sym && sym->type == TYPE_SET) {
                        $$ = strdup($1);
                    } else {
                        $$ = $1;
                    }
                }
            }
            | SIZE expression SIZE {
                $$ = malloc(strlen($2) + 30);
                sprintf($$, "set_size(%s)", $2);
                free($2);
            }
            ;

// set_operation: IDENTIFIER AND IDENTIFIER {
//                 Symbol* sym1 = lookup_symbol($1);
//                 Symbol* sym2 = lookup_symbol($3);
//                 if (sym1 == NULL || sym2 == NULL) {
//                     yyerror("Undefined variable");
//                 } else if (sym1->type != TYPE_SET || sym2->type != TYPE_SET) {
//                     yyerror("Variable is not a set");
//                 } else {
//                     $$ = malloc(strlen($1) + strlen($3) + 30);
//                     sprintf($$, "set_intersection(%s, %s)", $1, $3);
//                 }
//                 free($1);
//                 free($3);
//             }
//             | IDENTIFIER PLUS IDENTIFIER {
//                 Symbol* sym1 = lookup_symbol($1);
//                 Symbol* sym2 = lookup_symbol($3);
//                 if (sym1 == NULL || sym2 == NULL) {
//                     yyerror("Undefined variable");
//                 } else if (sym1->type != TYPE_SET || sym2->type != TYPE_SET) {
//                     yyerror("Variable is not a set");
//                 } else {
//                     $$ = malloc(strlen($1) + strlen($3) + 30);
//                     sprintf($$, "set_union(%s, %s)", $1, $3);
//                 }
//                 free($1);
//                 free($3);
//             }
//             | IDENTIFIER MINUS IDENTIFIER {
//                 Symbol* sym1 = lookup_symbol($1);
//                 Symbol* sym2 = lookup_symbol($3);
//                 if (sym1 == NULL || sym2 == NULL) {
//                     yyerror("Undefined variable");
//                 } else if (sym1->type != TYPE_SET || sym2->type != TYPE_SET) {
//                     yyerror("Variable is not a set");
//                 } else {
//                     $$ = malloc(strlen($1) + strlen($3) + 30);
//                     sprintf($$, "set_difference(%s, %s)", $1, $3);
//                 }
//                 free($1);
//                 free($3);
//             }
//             | SIZE IDENTIFIER {
//                 Symbol* sym = lookup_symbol($2);
//                 if (sym == NULL) {
//                     yyerror("Undefined variable");
//                 } else if (sym->type != TYPE_SET) {
//                     yyerror("Size operation can only be applied to sets/collections");
//                 } else {
//                     $$ = malloc(strlen($2) + 20);
//                     sprintf($$, "set_size(%s)", $2);
//                 }
//             }
//             ;

// collection_operation: IDENTIFIER AND IDENTIFIER {
//                         Symbol* sym1 = lookup_symbol($1);
//                         Symbol* sym2 = lookup_symbol($3);
//                         if (sym1 == NULL || sym2 == NULL) {
//                             yyerror("Undefined variable");
//                         } else if (sym1->type != TYPE_COLLECTION || sym2->type != TYPE_COLLECTION) {
//                             yyerror("Variable is not a collection");
//                         } else {
//                             $$ = malloc(strlen($1) + strlen($3) + 30);
//                             sprintf($$, "collection_intersection(%s, %s)", $1, $3);
//                         }
// }

expression_list: expression { $$ = $1; }
                | expression_list COMMA expression {
                    $$ = malloc(strlen($1) + strlen($3) + 3);
                    sprintf($$, "%s, %s", $1, $3);
                    free($1);
                    free($3);
                }
                ;

expression: INTEGER {
                $$ = malloc(20);
                sprintf($$, "%d", $1);
            }
            | STRING { $$ = strdup($1); }
            | IDENTIFIER {
                if (lookup_symbol($1) == NULL) {
                    yyerror("Undefined variable");
                }
                $$ = strdup($1);
            }
            | expression AND expression {
                $$ = malloc(strlen($1) + strlen($3) + 30);
                SymbolType type1 = get_expression_type($1);
                SymbolType type2 = get_expression_type($3);
                if (type1 == TYPE_SET && type2 == TYPE_SET) {
                    sprintf($$, "set_intersection(%s, %s)", $1, $3);
                } else if (type1 == TYPE_COLLECTION && type2 == TYPE_COLLECTION) {
                    sprintf($$, "collection_intersection(%s, %s)", $1, $3);
                } else {
                    yyerror("AND operation can only be applied to sets/collections");
                }
                free($1);
                free($3);
            }
            | expression PLUS expression {
                $$ = malloc(strlen($1) + strlen($3) + 30);
                SymbolType type1 = get_expression_type($1);
                SymbolType type2 = get_expression_type($3);
                if (type1 == TYPE_SET && type2 == TYPE_SET) {
                    sprintf($$, "set_union(%s, %s)", $1, $3);
                } else if (type1 == TYPE_COLLECTION && type2 == TYPE_COLLECTION) {
                    sprintf($$, "collection_union(%s, %s)", $1, $3);
                } else if (type1 == TYPE_SET && type2 == TYPE_INT) {
                    sprintf($$, "set_add(%s, %s)", $1, $3);
                } else if (type1 == TYPE_COLLECTION && type2 == TYPE_STR) {
                    sprintf($$, "collection_add(%s, %s)", $1, $3);
                } else if (type1 == TYPE_INT && type2 == TYPE_INT) {
                    sprintf($$, "%s + %s", $1, $3);
                } else {
                    yyerror("PLUS operation not supported for these types");
                }
                free($1);
                free($3);
            }
            | expression MINUS expression {
                $$ = malloc(strlen($1) + strlen($3) + 30);
                SymbolType type1 = get_expression_type($1);
                SymbolType type2 = get_expression_type($3);
                if (type1 == TYPE_SET && type2 == TYPE_SET) {
                    sprintf($$, "set_difference(%s, %s)", $1, $3);
                } else if (type1 == TYPE_COLLECTION && type2 == TYPE_COLLECTION) {
                    sprintf($$, "collection_difference(%s, %s)", $1, $3);
                } else if (type1 == TYPE_SET && type2 == TYPE_INT) {
                    sprintf($$, "set_remove(%s, %s)", $1, $3);
                } else if (type1 == TYPE_COLLECTION && type2 == TYPE_STR) {
                    sprintf($$, "collection_remove(%s, %s)", $1, $3);
                } else if (type1 == TYPE_INT && type2 == TYPE_INT) {
                    sprintf($$, "%s - %s", $1, $3);
                } else {
                    yyerror("MINUS operation not supported for these types");
                }
                free($1);
                free($3);
            }
            | expression MULTIPLY expression {
                $$ = malloc(strlen($1) + strlen($3) + 4);
                sprintf($$, "%s * %s", $1, $3);
                free($1);
                free($3);
            }
            | expression DIVIDE expression {
                $$ = malloc(strlen($1) + strlen($3) + 4);
                sprintf($$, "%s / %s", $1, $3);
                free($1);
                free($3);
            }
            | LPAREN expression RPAREN {
                $$ = malloc(strlen($2) + 3);
                sprintf($$, "(%s)", $2);
                free($2);
            }
            | set_expression { $$ = $1; }
            | collection_expression { $$ = $1; }
            ;

set_expression: LBRACKET RBRACKET { 
                    $$ = strdup("set_new()"); 
                    printf("Debug: Created empty set\n");
                }
                |LBRACKET element_list RBRACKET {
                    printf("Debug: Set expression with elements\n");
                    char* temp = malloc(strlen($2) + 50); // increased buffer size
                    int count = 1; // start with 1 for the first element
                    for (int i = 0; $2[i] != '\0'; i++) {
                        if ($2[i] == ',') { // count the number of commas
                            count++;
                        }
                    }
                    sprintf(temp, "set_from_array(%d, %s)", count, $2);
                    $$ = temp;
                    printf("Created set: %s\n", $$);
                    free($2);
                }
                ;
        
collection_expression: LBRACE RBRACE { $$ = strdup("collection_new()"); }
                    | LBRACE element_list RBRACE {
                        char* temp = malloc(strlen($2) + 50); // increased buffer size
                        int count = 1; // start with 1 for the first element
                        for (int i = 0; $2[i] != '\0'; i++) {
                            if ($2[i] == ',') { // count the number of commas
                                count++;
                            }
                        }
                        sprintf(temp, "collection_from_array(%d, %s)", count, $2);
                        $$ = temp;
                        free($2);
                    }
                    ;

element_list: expression { 
                printf("Debug: Element list with single expression\n");
                $$ = $1; 
            }
            | element_list COMMA expression {
                printf("Debug: Element list with multiple expressions\n");
                $$ = malloc(strlen($1) + strlen($3) + 3);
                sprintf($$, "%s, %s", $1, $3);
                free($1);
                free($3);
            }
            ;

condition: expression EQUAL expression {
                $$ = malloc(strlen($1) + strlen($3) + 4);
                sprintf($$, "%s == %s", $1, $3);
                free($1);
                free($3);
            }
            | expression LESS expression {
                $$ = malloc(strlen($1) + strlen($3) + 4);
                sprintf($$, "%s < %s", $1, $3);
                free($1);
                free($3);
            }
            | expression GREATER expression {
                $$ = malloc(strlen($1) + strlen($3) + 4);
                sprintf($$, "%s > %s", $1, $3);
                free($1);
                free($3);
            }
            | expression LESS_EQUAL expression {
                $$ = malloc(strlen($1) + strlen($3) + 5);
                sprintf($$, "%s <= %s", $1, $3);
                free($1);
                free($3);
            }
            | expression GREATER_EQUAL expression {
                $$ = malloc(strlen($1) + strlen($3) + 5);
                sprintf($$, "%s >= %s", $1, $3);
                free($1);
                free($3);
            }
            | NOT condition {
                $$ = malloc(strlen($2) + 3);
                sprintf($$, "!%s", $2);
                free($2);
            }
            | set_expression {
                $$ = malloc(strlen($1) + 10);
                sprintf($$, "!set_is_empty(%s)", $1);
                free($1);
            }
            | collection_expression {
                $$ = malloc(strlen($1) + 20);
                sprintf($$, "!collection_is_empty(%s)", $1);
                free($1);
            }
            | expression {
                Symbol* sym = lookup_symbol($1);
                if (sym && sym->type == lookup_symbol($1)) {
                    $$ = malloc(strlen($1) + 20);
                    sprintf($$, "!set_is_empty(%s)", $1);
                } else {
                    $$ = strdup($1);
                }
                free($1);
            }
            ;

set_or_collection: IDENTIFIER {
                    Symbol* sym = lookup_symbol($1);
                    if (sym == NULL) {
                        yyerror("Undefined variable");
                    } else if (sym->type != TYPE_SET && sym->type != TYPE_COLLECTION) {
                        yyerror("Variable is not a set or collection");
                    }
                    $$ = strdup($1);
                }
            ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error on line %d: %s\n", yylineno, s);
    fprintf(stderr, "Near token: %s\n", yytext);
    exit(1); //Exit on error to avoid silent failures
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }
    
    yyout = fopen(argv[2], "w");
    if (!yyout) {
        perror("Error opening output file");
        return 1;
    }

    yyin = input;
    init_symbol_table();

    //Write necessary includes and function prototypes
    fprintf(yyout, "#include <stdio.h>\n");
    fprintf(yyout, "#include <stdlib.h>\n");
    fprintf(yyout, "#include \"setlang_runtime.h\"\n");
    fprintf(yyout, "int main() {\n");


    printf("Starting to parse...\n");
    int result = yyparse();
    printf("Parsing finished with result: %d.\n", result);
    fprintf(yyout, "// Cleanup\n");
    for (int i = 0; i < table_size; i++) {
        if (symbol_table[i] && symbol_table[i]->type == TYPE_SET) {
            fprintf(yyout, "set_free(%s);\n", symbol_table[i]->name);
        }
    }
    //Close main function
    fprintf(yyout, "return 0;\n}\n");

    free_symbol_table();
    
    if (result == 0) {
        printf("Parsing completed successfully.\n");
    } else {
        printf("Parsing failed.\n");
    }
    
    fclose(input);
    fclose(yyout);
    return result;
}
