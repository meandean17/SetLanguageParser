#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "setlang_runtime.h"
int main()
{
    collection_t *class = collection_new();
    collection_t *highGradeStudents = collection_new();
    collection_t *lowGradeStudents = collection_new();
    collection_t *avgGradeStudents = collection_new();

    set_t *grades = set_new();
    set_t *gradesHigh = set_new();

    int grd;
    char *student = NULL;
    collection_free(class);
    class = collection_from_array(10, "Rafi_Suisa", "Tamar_Even", "Avi_Maoz", "Eli_Kamer", "Shlomit_Raz", "Haim_Mizrachi", "Moshe_Samocha", "Tali_Raban", "Sharon_Tal", "Gal_Elbaz");
    set_free(gradesHigh);
    gradesHigh = set_new();
    collection_free(highGradeStudents);
    highGradeStudents = collection_new();
    {
        iterator_t it = iterator_new(class, false);
        while (iterator_has_next(&it))
        {
            student = (char *)iterator_next(&it);

            printf("Grade for:");
            printf("%s", student);
            printf("\n");

            printf(">");
            if (scanf("%d", &grd) != 1)
            {
                fprintf(stderr, "Invalid input\n");
                exit(1);
            }
            while (getchar() != '\n')
                ; // Clear input buffer

            set_add(grades, grd);
            if (grd >= 90)
            {

                set_add(gradesHigh, grd);
                collection_add(highGradeStudents, student);
            }
        }
        iterator_free(&it);
    }

    if (!set_is_empty(gradesHigh))
    {

        printf("Number of top grades:");
        printf("%d", set_size(gradesHigh));
        printf("\n");

        printf("Top Grades are:");
        set_print(gradesHigh);
        printf("\n");

        printf("High Grade Students are:");
        collection_print(highGradeStudents);
        printf("\n");
    }
    printf("Low-grade students >");
    {
        char temp[1000];
        if (fgets(temp, sizeof(temp), stdin) == NULL)
        {
            fprintf(stderr, "Invalid input\n");
            exit(1);
        }
        temp[strcspn(temp, "\n")] = '\0'; // Remove newline
        char *token = strtok(temp, ",");
        while (token != NULL)
        {
            char *value = strdup(token);
            char *end = value + strlen(value) - 1;
            while (end > value && isspace(*end))
                end--;
            *(end + 1) = '\0'; // Remove trailing spaces
            char *start = value;
            while (*start && isspace(*start))
                start++;
            memmove(value, start, strlen(start) + 1); // Remove leading spaces
            collection_add(lowGradeStudents, value);
            free(value);
            token = strtok(NULL, ",");
        }
    }

    {
        iterator_t it = iterator_new(lowGradeStudents, false);
        while (iterator_has_next(&it))
        {
            student = (char *)iterator_next(&it);
            printf("Get better next time:");
            printf("%s", student);
            printf("\n");
        }
        iterator_free(&it);
    }

    collection_free(avgGradeStudents);
    avgGradeStudents = collection_difference(collection_difference(class, highGradeStudents), lowGradeStudents);
    printf("Students with good grades:");
    collection_print(avgGradeStudents);
    printf("\n");

    // Cleanup
    set_free(grades);
    collection_free(avgGradeStudents);
    collection_free(highGradeStudents);
    collection_free(class);
    set_free(gradesHigh);
    collection_free(lowGradeStudents);
    return 0;
}
