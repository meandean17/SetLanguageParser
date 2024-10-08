#ifndef SETLANG_RUNTIME_H
#define SETLANG_RUNTIME_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct set_t set_t;
typedef struct collection_t collection_t;
typedef struct {
    void* container;
    int current;
    bool is_set;
} iterator_t;

set_t* set_new();
void set_free(set_t* set);
bool set_contains(set_t* set, int value);
set_t* set_add(set_t* set, int value);
set_t* set_from_array(int count, ...);
int set_size(set_t* set);
set_t* set_union(set_t* set1, set_t* set2);
set_t* set_intersection(set_t* set1, set_t* set2);
set_t* set_difference(set_t* set1, set_t* set2);
set_t* set_remove(set_t* set, int value);
void set_print(set_t* set);
bool set_is_empty(set_t* set);
bool set_equals(set_t* set1, set_t* set2);

collection_t* collection_new();
void collection_free(collection_t* collection);
bool collection_contains(collection_t* collection, char* value);
collection_t* collection_add(collection_t* collection, char* value);
collection_t* collection_from_array(int count, ...);
int collection_size(collection_t* collection);
collection_t* collection_union(collection_t* collection1, collection_t* collection2);
collection_t* collection_intersection(collection_t* collection1, collection_t* collection2);
collection_t* collection_difference(collection_t* collection1, collection_t* collection2);
collection_t* collection_remove(collection_t* collection, char* value);
void collection_print(collection_t* collection);
bool collection_is_empty(collection_t* collection);
bool collection_equals(collection_t* collection1, collection_t* collection2);

iterator_t iterator_new(void* container, bool is_set);
bool iterator_has_next(iterator_t* it);
void* iterator_next(iterator_t* it);
void iterator_free(iterator_t* it);

#endif
