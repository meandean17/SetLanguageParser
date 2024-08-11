#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_STR,
    TYPE_SET,
    TYPE_COLLECTION,
} SymbolType;

typedef struct {
    char* name;
    SymbolType type;
    union {
        int ival;
        char* sval;
    };
} Symbol;

extern Symbol** symbol_table;
extern int table_size;

void init_symbol_table();
bool insert_symbol(const char* name, SymbolType type);
Symbol* lookup_symbol(const char* name);
void free_symbol_table();

#endif