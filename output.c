#include <stdio.h>
#include <stdlib.h>
#include "setlang_runtime.h"
int main() {
collection_t* c1 = collection_new();
collection_t* c2 = collection_new();
collection_t* c3 = collection_new();

int a;
collection_free(c1);
c1 = collection_from_array(3, "apple", "banana", "cherry");
collection_free(c2);
c2 = collection_from_array(3, "banana", "date", "elderberry");
a = 5;
printf("Initial collections:");
printf("\n");

printf("c1: ");
collection_print(c1);
printf("\n");

printf("c2: ");
collection_print(c2);
printf("\n");

collection_free(c3);
c3 = collection_union(c1, c2);
printf("c3 (c1 union c2): ");
collection_print(c3);
printf("\n");

c1 = collection_remove(c1, "apple");
printf("c1 after removing 'apple': ");
collection_print(c1);
printf("\n");

c2 = collection_add(c2, "fig");
printf("c2 after adding 'fig': ");
collection_print(c2);
printf("\n");

if (!collection_is_empty(c1)) {
printf("c1 is not empty");
printf("\n");

printf("c1 has ");
printf("%d", collection_size(c1));
printf(" elements");
printf("\n");

} else {
printf("c1 is empty");
printf("\n");

}// Cleanup
collection_free(c1);
collection_free(c2);
collection_free(c3);
return 0;
}
