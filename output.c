#include <stdio.h>
#include <stdlib.h>
#include "setlang_runtime.h"
int main()
{
    int a, b;
    set_t *s1 = set_new();
    set_t *s2 = set_new();
    set_t *s3 = set_new();
    set_t *s4 = set_new();
    set_t *empty = set_new();

    set_free(s1);
    s1 = set_from_array(5, 1, 2, 3, 4, 5);
    set_free(s2);
    s2 = set_from_array(5, 3, 4, 5, 6, 7);
    a = 3;
    b = 8;
    printf("Initial sets:");
    printf("\n");

    printf("s1: ");
    set_print(s1);
    printf("\n");

    printf("s2: ");
    set_print(s2);
    printf("\n");

    printf("empty: ");
    set_print(empty);
    printf("\n");

    set_add(s1, a);
    printf("s1 after adding 3 (should be unchanged): ");
    set_print(s1);
    printf("\n");

    set_add(s1, b);
    printf("s1 after adding 8: ");
    set_print(s1);
    printf("\n");

    set_remove(s2, a);
    printf("s2 after removing 3: ");
    set_print(s2);
    printf("\n");

    set_free(s3);
    s3 = set_intersection(s1, s2);
    printf("s3 (s1 intersection s2): ");
    set_print(s3);
    printf("\n");

    set_free(s4);
    s4 = set_union(s1, s2);
    printf("s4 (s1 union s2): ");
    set_print(s4);
    printf("\n");

    set_free(s4);
    s4 = set_difference(s1, s2);
    printf("s4 (s1 difference s2): ");
    set_print(s4);
    printf("\n");

    printf("Size of s1: ");
    printf("%d", set_size(s1));
    printf("\n");

    printf("Size of empty set: ");
    printf("%d", set_size(empty));
    printf("\n");

    s3 = set_union(s3, set_from_array(2, 9, 10));
    printf("s3 after adding [9, 10]: ");
    set_print(s3);
    printf("\n");

    if (!set_is_empty(s1))
    {

        printf("s1 is not empty");
        printf("\n");
    }
    if (!!set_is_empty(empty))
    {

        printf("empty set is empty");
        printf("\n");
    }
    set_free(s1);
    s1 = set_new();
    printf("s1 after setting to empty set: ");
    set_print(s1);
    printf("\n");
    // Cleanup
    set_free(s1);
    set_free(s2);
    set_free(s3);
    set_free(s4);
    set_free(empty);
    return 0;
}
