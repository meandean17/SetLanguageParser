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
        if (strncmp(expr, "set_", 4) == 0 || strncmp(expr, "(set_", 5 == 0)) {
            return TYPE_SET;
        } else if (strncmp(expr, "collection_", 11) == 0 || strncmp(expr, "(collection_", 12 == 0)) {
            return TYPE_COLLECTION;
        } else if (expr[0] >= '0' && expr[0] <= '9') {
            return TYPE_INT;
        } else if (is_string(expr)) {
            return TYPE_STR;
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
%token PLUS MINUS MULTIPLY DIVIDE MOD AND ASSIGN EQUAL LESS GREATER LESS_EQUAL GREATER_EQUAL NOT

%type <code> expression statement statement_list declaration assignment if_statement while_statement for_statement input_statement output_statement
%type <code> set_expression collection_expression element_list condition
%type <code> identifier_list
%type <code> expression_list
%type <code> set_or_collection
%type <code> output_list output_item

%left AND
%left EQUAL LESS GREATER LESS_EQUAL GREATER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right UMINUS
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
            | LBRACE statement_list RBRACE {
                $$ = malloc(strlen($2) + 3);
                sprintf($$, "\n%s\n", $2);
                free($2);
            }
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
                printf("Temp: %s\n", temp);
                $$ = malloc(1);
                $$[0] = '\0';
                while (token != NULL) {
                    printf("Debug: Token: %s\n", token);
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
            | COLLECTION { 
                current_type = TYPE_COLLECTION; 
                printf("Debug: Entering COLLECTION rule");  // Debug print
            } identifier_list SEMICOLON {
                printf("Debug: Finishing COLLECTION rule. Identifier list: %s\n", $3);
                printf("Declaring COLLECTION: %s\n", $3);  // Debug print
                char* temp = strdup($3);
                printf("Temp: %s\n", temp);
                char* token = strtok(temp, ",");
                $$ = malloc(1);
                $$[0] = '\0';
                while (token != NULL) {
                    char* trimmed = token;
                    while (*trimmed == ' ') trimmed++; // trim leading spaces
                    char* end = trimmed + strlen(trimmed) - 1;
                    while (end > trimmed && *end == ' ') end--; // trim trailing spaces
                    *(end + 1) = '\0';

                    char* new_decl = malloc(strlen(trimmed) + 40);
                    sprintf(new_decl, "collection_t* %s = collection_new();\n", trimmed);

                    $$ = realloc($$, strlen($$) + strlen(new_decl) + 10);
                    printf("Debug: new_decl: %s\n", new_decl);
                    strcat($$, new_decl);

                    free(new_decl);
                    token = strtok(NULL, ",");
                }
                free(temp);
                free($3);
                printf("Debug: COLLECTION declaration completed\n");
            }
            ;

identifier_list: IDENTIFIER {
                    printf("Debug: Identifier list with single identifier: %s\n", $1);  // Debug print
                    if (!insert_symbol($1, current_type)) {
                        yyerror("Symbol already defined");
                    }
                    $$ = strdup($1);
                }
                | identifier_list COMMA IDENTIFIER {
                    printf("Debug: Identifier list with multiple identifiers: %s\n", $3);  // Debug print
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
                    if(strncmp($3, "set_add", 7) == 0 || strncmp($3, "set_remove", 10) == 0 || strncmp($3, "collection_add", 14) == 0 || strncmp($3, "collection_remove", 17) == 0) {
                        // for set_add and set_remove collection_add collection_remove, dont assign result
                        $$ = malloc(strlen($3) + 2);
                        sprintf($$, "%s;", $3);
                    } else if (sym->type == TYPE_SET && type == TYPE_SET) {
                        //only free if the variable is not used in the expression
                        if (strstr($3, $1) == NULL) {
                            $$ = malloc(strlen($1) + strlen($3) + 50);
                            sprintf($$, "set_free(%s);\n%s = %s;", $1, $1, $3);
                        } else {
                            $$ = malloc(strlen($1) + strlen($3) + 5);
                            sprintf($$, "%s = %s;", $1, $3);
                        }
                    } else if (sym->type == TYPE_COLLECTION && type == TYPE_COLLECTION) { 
                        if (strstr($3, $1) == NULL) {
                            $$ = malloc(strlen($1) + strlen($3) + 50);
                            sprintf($$, "collection_free(%s);\n%s = %s;", $1, $1, $3);
                        } else {
                            $$ = malloc(strlen($1) + strlen($3) + 5);
                            sprintf($$, "%s = %s;", $1, $3);
                        }
                    }
                     else {
                        $$ = malloc(strlen($1) + strlen($3) + 5);
                        sprintf($$, "%s = %s;", $1, $3);
                    }
                }
                free($1);
                free($3);
            }
            ;

if_statement: IF LPAREN condition RPAREN statement {
                $$ = malloc(strlen($3) + strlen($5) + 20);
                sprintf($$, "if (%s) {\n%s\n}", $3, $5);
                free($3);
                free($5);
            }
            | IF LPAREN condition RPAREN LBRACE statement_list RBRACE {
                $$ = malloc(strlen($3) + strlen($6) + 20);
                sprintf($$, "if (%s) {\n%s\n}", $3, $6);
                free($3);
                free($6);
            }
            | IF LPAREN condition RPAREN statement ELSE statement {
                $$ = malloc(strlen($3) + strlen($5) + strlen($7) + 30);
                sprintf($$, "if (%s) {\n%s\n} else {\n%s\n}", $3, $5, $7);
                free($3);
                free($5);
                free($7);
            }
            | IF LPAREN condition RPAREN LBRACE statement_list RBRACE ELSE LBRACE statement_list RBRACE {
                $$ = malloc(strlen($3) + strlen($6) + strlen($10) + 40);
                sprintf($$, "if (%s) {\n%s\n} else {\n%s\n}", $3, $6, $10);
                free($3);
                free($6);
                free($10);
            }
            ;

while_statement: WHILE LPAREN condition RPAREN statement {
                    $$ = malloc(strlen($3) + strlen($5) + 50);
                    sprintf($$, "while (%s) {\n%s\n}", $3, $5);
                    free($3);
                    free($5);
                }
                |
                WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE {
                    $$ = malloc(strlen($3) + strlen($6) + 50);
                    sprintf($$, "while (%s) {\n%s\n}", $3, $6);
                    free($3);
                    free($6);
                }
                ;

for_statement: FOR LPAREN IDENTIFIER COLON set_or_collection RPAREN statement {
                    Symbol *sym = lookup_symbol($5);
                    char* type = sym->type == TYPE_SET ? "int" : "char*";
                    $$ = malloc(strlen($3) + strlen($5) + strlen($7) + 200);
                    sprintf($$, "{\n"
                                "iterator_t it = iterator_new(%s, %s);\n"
                                "while (iterator_has_next(&it)) {\n"
                                "%s = (%s)iterator_next(&it);\n"
                                "%s\n"
                                "}\n"
                                "iterator_free(&it);\n"
                                "}\n", $5, (sym->type == TYPE_SET ? "true" : "false"), $3, type, $7);
                    free($3);
                    free($5);
                    free($7);
                }
                | FOR LPAREN IDENTIFIER COLON set_or_collection RPAREN LBRACE statement_list RBRACE {
                    Symbol *sym = lookup_symbol($5);
                    char* type = sym->type == TYPE_SET ? "int" : "char*";
                    $$ = malloc(strlen($3) + strlen($5) + strlen($8) + 200);
                    sprintf($$, "{\n"
                                "iterator_t it = iterator_new(%s, %s);\n"
                                "while (iterator_has_next(&it)) {\n"
                                "%s = (%s)iterator_next(&it);\n"
                                "%s\n"
                                "}\n"
                                "iterator_free(&it);\n"
                                "}\n", $5, (sym->type == TYPE_SET ? "true" : "false"), $3, type, $8);
                    free($3);
                    free($5);
                    free($8);
                }
                ;

input_statement: INPUT expression IDENTIFIER SEMICOLON {
                Symbol* sym = lookup_symbol($3);
                if (sym == NULL) {
                    yyerror("Undefined variable");
                }
                $$ = malloc(strlen($2) + strlen($3) + 1000);
                switch(sym->type) {
                    case TYPE_INT:
                        sprintf($$, "printf(%s);\n"
                                    "if (scanf(\"%%d\", &%s) != 1) {\n"
                                    "   fprintf(stderr, \"Invalid input\\n\");\n"
                                    "   exit(1);\n"
                                    "}\n"
                                    "while (getchar() != '\\n'); // Clear input buffer\n", $2, $3);

                        break;
                    case TYPE_STR:
                        sprintf($$, "printf(%s);\n"
                                    "%s = malloc(1000);\n"
                                    "if (scanf(\"%%999s\", %s) != 1) {\n"
                                    "   fprintf(stderr, \"Invalid input\\n\");\n"
                                    "   exit(1);\n"
                                    "}\n", $2, $3, $3);
                        break;
                    case TYPE_SET:
                        sprintf($$, "printf(%s);\n"
                                    "char* temp[1000];\n"
                                    "if (fgets(temp, 1000, stdin) == NULL) {\n"
                                    "   fprintf(stderr, \"Invalid input\\n\");\n"
                                    "   exit(1);\n"
                                    "}\n"
                                    "char* token = strtok(temp, \",\");\n"
                                    "while (token != NULL) {\n"
                                    "   int value;\n"
                                    "   if (sscanf(token, \"%%d\", &value) != 1) {\n"
                                    "       set_add(%s, value);\n"
                                    "   }\n"
                                    "   token = strtok(NULL, \",\");\n"
                                    "}\n", $2, $3);
                        break;
                    case TYPE_COLLECTION:
                        printf("Debug: Generating input statement for collection %s\n", $3);
                        sprintf($$, "printf(%s);\n"
                                    "{\n"
                                    "    char temp[1000];\n"
                                    "    if (fgets(temp, sizeof(temp), stdin) == NULL) {\n"
                                    "        fprintf(stderr, \"Invalid input\\n\");\n"
                                    "        exit(1);\n"
                                    "    }\n"
                                    "    temp[strcspn(temp, \"\\n\")] = '\\0';  // Remove newline\n"
                                    "    char* token = strtok(temp, \",\");\n"
                                    "    while (token != NULL) {\n"
                                    "        char* value = strdup(token);\n"
                                    "        char* end = value + strlen(value) - 1;\n"
                                    "        while (end > value && isspace(*end)) end--;\n"
                                    "        *(end+1) = '\\0';  // Remove trailing spaces\n"
                                    "        char* start = value;\n"
                                    "        while (*start && isspace(*start)) start++;\n"
                                    "        memmove(value, start, strlen(start) + 1);  // Remove leading spaces\n"
                                    "        collection_add(%s, value);\n"
                                    "        free(value);\n"
                                    "        token = strtok(NULL, \",\");\n"
                                    "    }\n"
                                    "}\n", $2, $3);
                        printf("Debug: Generated input statement for collection %s\n", $3);
                        break;
                    default:
                        yyerror("Unsupported type for input");
                }
                free($2);
                free($3);
                }
                ;

output_statement: OUTPUT output_list SEMICOLON {
                    $$ = malloc(strlen($2) + 100);
                    strcpy($$, "");
                    char *token = strtok($2, ";");
                    while (token != NULL) {
                        char *temp = malloc(strlen(token) + 100);
                        if (token[0] == '"') { // String literal
                            // sprintf(temp, "printf(%s);\n", token);
                            char *escaped = malloc(strlen(token) * 2 + 1);
                            char *p = escaped;
                            for (char *c = token; *c; c++) {
                                if (*c == '%') {
                                    *p++ = '%';
                                    *p++ = '%';
                                } else {
                                    *p++ = *c;
                                }
                            }
                            *p = '\0';
                            sprintf(temp, "printf(%s);\n", escaped);
                            free(escaped);
                        } else if (strstr(token, "set_size") != NULL) { // Set size
                            char *set_name = strdup(token + 9); // skip "set_size("
                            set_name[strlen(set_name) - 1] = '\0'; // remove trailing ')'
                            sprintf(temp, "printf(\"%%d\", set_size(%s));\n", set_name);
                            free(set_name);
                        }  else if (strstr(token, "collection_size") != NULL) { // Collection size
                            char *collection_name = strdup(token + 16); // skip "collection_size("
                            collection_name[strlen(collection_name) - 1] = '\0'; // remove trailing ')'
                            sprintf(temp, "printf(\"%%d\", collection_size(%s));\n", collection_name);
                            free(collection_name);
                        } else {
                            if (get_expression_type(token) == TYPE_SET) {
                                sprintf(temp, "set_print(%s);\n", token);
                            } else if (get_expression_type(token) == TYPE_COLLECTION) {
                                sprintf(temp, "collection_print(%s);\n", token);
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
                                } else if (sym->type == TYPE_STR) {
                                    sprintf(temp, "printf(\"%%s\", %s);\n", token);
                                } else {
                                    yyerror("Unsupported type for output");
                                }
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
                    if(get_expression_type($1) == TYPE_SET || get_expression_type($1) == TYPE_COLLECTION) {
                        $$ = $1;
                    } else {
                        printf("Debug: Output item: %s\n", $1);
                        Symbol *sym = lookup_symbol($1);
                        if ((sym && sym->type == TYPE_SET) || (sym->type == TYPE_COLLECTION)) {
                            $$ = strdup($1);
                        } else {
                            $$ = $1;
                        }
                    }
                }
            }
            | SIZE expression SIZE {
                Symbol *sym = lookup_symbol($2);
                if(sym && sym->type == TYPE_SET) {
                    $$ = malloc(strlen($2) + 20);
                    sprintf($$, "set_size(%s)", $2);
                } else if(sym && sym->type == TYPE_COLLECTION) {
                    $$ = malloc(strlen($2) + 30);
                    sprintf($$, "collection_size(%s)", $2);
                } else {
                    yyerror("SIZE can only be applied to sets/collections");
                }
                free($2);
            }
            ;


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
            | MINUS expression %prec UMINUS {
                $$ = malloc(strlen($2) + 4);
                sprintf($$, "-%s", $2);
                free($2);
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
                    if(is_string($3)) {
                        sprintf($$, "collection_remove(%s, %s)", $1, $3);
                    } else {
                        sprintf($$, "collection_remove(%s,%s)", $1, $3);
                    }
                } else if (type1 == TYPE_INT && type2 == TYPE_INT) {
                    sprintf($$, "%s - %s", $1, $3);
                } else {
                    yyerror("MINUS operation not supported for these types ");
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
            | expression MOD expression {
                SymbolType type1 = get_expression_type($1);
                SymbolType type2 = get_expression_type($3);
                if (type1 != TYPE_INT || type2 != TYPE_INT) {
                    yyerror("MOD operation can only be applied to integers");
                } else {
                    $$ = malloc(strlen($1) + strlen($3) + 4);
                    sprintf($$, "%s %% %s", $1, $3);
                }
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
        
collection_expression: LBRACE RBRACE { 
                        $$ = strdup("collection_new()"); 
                        printf("Debug: Created empty collection\n");
                    }
                    | LBRACE element_list RBRACE {
                        printf("Debug: Collection expression with elements\n");
                        char* temp = malloc(strlen($2) + 50); // increased buffer size
                        int count = 1; // start with 1 for the first element
                        for (int i = 0; $2[i] != '\0'; i++) {
                            if ($2[i] == ',') { // count the number of commas
                                count++;
                            }
                        }
                        sprintf(temp, "collection_from_array(%d, %s)", count, $2);
                        $$ = temp;
                        printf("Created collection: %s\n", $$);
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
            | expression NOT ASSIGN expression {
                $$ = malloc(strlen($1) + strlen($4) + 6);
                sprintf($$, "%s != %s", $1, $4);
                free($1);
                free($4);
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
                if (sym && sym->type == TYPE_SET) {
                    $$ = malloc(strlen($1) + 20);
                    sprintf($$, "!set_is_empty(%s)", $1);
                } else if (sym && sym->type == TYPE_COLLECTION) {
                    $$ = malloc(strlen($1) + 30);
                    sprintf($$, "!collection_is_empty(%s)", $1);
                } else {
                    $$ = strdup($1);
                }
                free($1);
            }
            ;

set_or_collection: IDENTIFIER {
                    printf("Debug: Set or collection: %s\n", $1);
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
    fprintf(yyout, "#include <string.h>\n");
    fprintf(yyout, "#include <ctype.h>\n");
    fprintf(yyout, "#include \"setlang_runtime.h\"\n");
    fprintf(yyout, "int main() {\n");


    printf("Starting to parse...\n");
    int result = yyparse();
    printf("Parsing finished with result: %d.\n", result);
    fprintf(yyout, "\n// Cleanup\n");
    for (int i = 0; i < table_size; i++) {
        if(symbol_table[i]) {
            if (symbol_table[i]->type == TYPE_SET) {
                fprintf(yyout, "set_free(%s);\n", symbol_table[i]->name);
            } else if (symbol_table[i]->type == TYPE_COLLECTION) {
                fprintf(yyout, "collection_free(%s);\n", symbol_table[i]->name);
            }
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
