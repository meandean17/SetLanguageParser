#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INITIAL_SIZE 100

Symbol** symbol_table;
int table_size;


// set all entries to null
void init_symbol_table() {
    table_size = INITIAL_SIZE;
    symbol_table = malloc(table_size * sizeof(Symbol*));
    if (symbol_table == NULL) {
        fprintf(stderr, "Failed to allocate memory for symbol table\n");
        exit(1);
    }
    for (int i = 0; i < table_size; i++) {
        symbol_table[i] = NULL;
    }
    printf("Symbol table initialized with size %d\n", table_size);
}

// convert string to index in table
unsigned int hash(const char* name) {
    unsigned int hash = 0;
    for(int i = 0; name[i] != '\0'; i++) {
        hash = 31 * hash + name[i];
    }
    return hash % table_size;
}

// insert a new symbol into the table
bool insert_symbol(const char* name, SymbolType type) {
    printf("Inserting symbol: %s\n", name);
    unsigned int index = hash(name);
    unsigned int original_index = index;

    printf("Initial index: %u\n", index);
    printf("Table size: %d\n", table_size);

    int collision_count = 0;
    while (symbol_table[index] != NULL) {
        printf("Collision at index %u\n", index);
        printf("Existing symbol at index %u: %s\n", index, symbol_table[index]->name);
        
        if (strcmp(symbol_table[index]->name, name) == 0) {
            printf("Symbol already exists\n");
            return false; // Symbol already exists
        }
 
        index = (index + 1) % table_size;
        collision_count++;
        
        if (collision_count >= table_size) {
            printf("Possible infinite loop detected\n");
            return false;
        }
        
        if (index == original_index) {
            printf("Table is full\n");
            return false; // table is full
        }
    }

    printf("Found empty slot at index %u\n", index);

    Symbol* new_symbol = malloc(sizeof(Symbol));
    if (new_symbol == NULL) {
        printf("Memory allocation failed for new symbol\n");
        return false;
    }

    new_symbol->name = strdup(name);
    if (new_symbol->name == NULL) {
        printf("Memory allocation failed for symbol name\n");
        free(new_symbol);
        return false;
    }

    new_symbol->type = type;
    symbol_table[index] = new_symbol;

    printf("Symbol inserted successfully\n");
    return true;
}

// find symbol by name
Symbol* lookup_symbol(const char* name) {
    printf("Looking up symbol: %s\n", name);  // Debug print
    unsigned int index = hash(name);
    unsigned int original_index = index;

    while (symbol_table[index] != NULL) {
        if (strcmp(symbol_table[index]->name, name) == 0)
            return symbol_table[index]; // Symbol found
 
        index = (index + 1) % table_size;
        if (index == original_index) 
            return NULL; // searched entire table
    }
    return NULL;
}

// free all memory used by the table
void free_symbol_table() {
    for(int i = 0; i < table_size; i++) {
        if(symbol_table[i]) {
            free(symbol_table[i]->name);
            free(symbol_table[i]);
        }
    }
    free(symbol_table);
}