#include "setlang_runtime.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

struct set_t {
    int size;
    int* elements;
    int capacity;
};

struct collection_t {
    int size;
    char** elements;
    int capacity;
};


set_t* set_new() {
    set_t* set = malloc(sizeof(set_t));
    set->size = 0;
    set->capacity = 0;
    set->elements = NULL;
    return set;
}

void set_free(set_t* set) {
    free(set->elements);
    free(set);
}

bool set_contains(set_t* set, int value) {
    for (int i = 0; i < set->size; i++) {
        if(set->elements[i] == value) {
            return true;
        }
    }
    return false;
}

set_t* set_add(set_t* set, int value) {
    if (!set_contains(set, value)) {
        if(set->size == set->capacity) {
            set->capacity = set->capacity == 0 ? 1 : set->capacity * 2;
            set->elements = realloc(set->elements, set->capacity * sizeof(int));
            if (set->elements == NULL) {
                //handle allocation failure (maybe)
                exit(1);
            }
        }
        set->elements[set->size] = value;
        set->size++;
    }
    return set;
}

set_t* set_from_array(int count, ...) {
    set_t* set = set_new();
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int);
        set_add(set, value);
    }
    va_end(args);
    return set;
}

int set_size(set_t* set) {
    return set->size;
}

set_t* set_union(set_t* set1, set_t* set2) {
    set_t* result = set_new();
    for (int i = 0; i < set1->size; i++) {
        set_add(result, set1->elements[i]);
    }
    for (int i = 0; i < set2->size; i++) {
        set_add(result, set2->elements[i]);
    }
    return result;
}

set_t* set_intersection(set_t* set1, set_t* set2) {
    set_t* result = set_new();
    for (int i = 0; i < set1->size; i++) {
        if(set_contains(set2, set1->elements[i])) {
            set_add(result, set1->elements[i]);
        }
    }
    return result;
}

set_t* set_difference(set_t* set1, set_t* set2) {
    set_t* result = set_new();
    for (int i = 0; i < set1->size; i++) {
        if(!set_contains(set2, set1->elements[i])) {
            set_add(result, set1->elements[i]);
        }
    }
    return result;
}

set_t* set_remove(set_t* set, int value) {
    for (int i = 0; i < set->size; i++) {
        if(set->elements[i] == value) {
            for (int j = i; j < set->size - 1; j++) {
                set->elements[j] = set->elements[j + 1];
            }
            set->size--;
            return set;
        }
    }
    return set;
}

void set_print(set_t* set) {
    printf("[");
    for (int i = 0; i < set->size; i++) {
        printf("%d", set->elements[i]);
        if (i < set->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

bool set_is_empty(set_t* set) {
    return set->size == 0;
}

// Set comparison functions
bool set_equals(set_t* set1, set_t* set2) {
    if (set1->size != set2->size) {
        return false;
    }
    for (int i = 0; i < set1->size; i++) {
        if (!set_contains(set2, set1->elements[i])) {
            return false;
        }
    }
    return true;
}

collection_t* collection_new() {
    collection_t* collection = malloc(sizeof(collection_t));
    collection->size = 0;
    collection->capacity = 0;
    collection->elements = NULL;
    return collection;
}

void collection_free(collection_t* collection) {
    for (int i = 0; i < collection->size; i++) {
        free(collection->elements[i]);
    }
    free(collection->elements);
    free(collection);
}

bool collection_contains(collection_t* collection, char* value) {
    for (int i = 0; i < collection->size; i++) {
        if(strcmp(collection->elements[i], value) == 0) {
            return true;
        }
    }
    return false;
}

collection_t* collection_add(collection_t* collection, char* value) {
    if (!collection_contains(collection, value)) {
        if(collection->size == collection->capacity) {
            collection->capacity = collection->capacity == 0 ? 1 : collection->capacity * 2;
            collection->elements = realloc(collection->elements, collection->capacity * sizeof(char*));
            if (collection->elements == NULL) {
                //handle allocation failure (maybe)
                exit(1);
            }
        }
        collection->elements[collection->size] = malloc(strlen(value) + 1);
        if(collection->elements[collection->size] == NULL) {
            //handle allocation failure (maybe)
            exit(1);
        }
        strcpy(collection->elements[collection->size], value);
        collection->size++;
    }
    return collection;
}

collection_t* collection_from_array(int count, ...) {
    collection_t* collection = collection_new();
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        char* value = va_arg(args, char*);
        collection_add(collection, value);
    }
    va_end(args);
    return collection;
}

int collection_size(collection_t* collection) {
    return collection->size;
}

collection_t* collection_union(collection_t* collection1, collection_t* collection2) {
    collection_t* result = collection_new();
    for (int i = 0; i < collection1->size; i++) {
        collection_add(result, collection1->elements[i]);
    }
    for (int i = 0; i < collection2->size; i++) {
        collection_add(result, collection2->elements[i]);
    }
    return result;
}

collection_t* collection_intersection(collection_t* collection1, collection_t* collection2) {
    collection_t* result = collection_new();
    for (int i = 0; i < collection1->size; i++) {
        if(collection_contains(collection2, collection1->elements[i])) {
            collection_add(result, collection1->elements[i]);
        }
    }
    return result;
}

collection_t* collection_difference(collection_t* collection1, collection_t* collection2) {
    collection_t* result = collection_new();
    for (int i = 0; i < collection1->size; i++) {
        if(!collection_contains(collection2, collection1->elements[i])) {
            collection_add(result, collection1->elements[i]);
        }
    }
    return result;
}

collection_t* collection_remove(collection_t* collection, char* value) {
    for (int i = 0; i < collection->size; i++) {
        if(strcmp(collection->elements[i], value) == 0) {
            for (int j = i; j < collection->size - 1; j++) {
                collection->elements[j] = collection->elements[j + 1];
            }
            collection->size--;
            return collection;
        }
    }
    return collection;
}

void collection_print(collection_t* collection) {
    printf("{");
    for (int i = 0; i < collection->size; i++) {
        printf("%s", collection->elements[i]);
        if (i < collection->size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
} 

bool collection_is_empty(collection_t* collection) {
    return collection->size == 0;
}

iterator_t iterator_new(void* container, bool is_set) {
    iterator_t it;
    it.container = container;
    it.current = 0;
    it.is_set = is_set;
    return it;
}

bool iterator_has_next(iterator_t* it) {
    if (it->is_set) {
        return it->current < ((set_t*)it->container)->size;
    } else {
        return it->current < ((collection_t*)it->container)->size;
    }
}

void* iterator_next(iterator_t* it) {
    if (iterator_has_next(it)) {
        if (it->is_set) {
            return &(((set_t*)it->container)->elements[it->current++]);
        } else {
            return ((collection_t*)it->container)->elements[it->current++];
        }
    }
    return NULL;
}

void iterator_free(iterator_t* it) {
    // Nothing to free in this simple implementation
    (void)it;
}

// Collection comparison functions
bool collection_equals(collection_t* col1, collection_t* col2) {
    if (col1->size != col2->size) {
        return false;
    }
    for (int i = 0; i < col1->size; i++) {
        if (!collection_contains(col2, col1->elements[i])) {
            return false;
        }
    }
    return true;
}