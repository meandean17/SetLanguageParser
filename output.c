#include <stdio.h>
#include <stdlib.h>
#include "setlang_runtime.h"
int main()
{
    collection_t *highTech = collection_new();
    collection_t *gaming = collection_new();

    collection_t *software = collection_new();
    collection_t *hardware = collection_new();
    collection_t *industrial = collection_new();

    collection_free(highTech);
    highTech = collection_from_array(7, "Apple", "Google", "Microsoft", "Nvidia", "Adobe", "Oracle", "Sap");
    highTech = collection_union(highTech, collection_from_array(6, "PayPal", "Nice", "Amdocs", "OpenAI", "Ford", "Mercedes"));
    collection_free(gaming);
    gaming = collection_from_array(6, "Sony", "Apple", "Microsoft", "Google", "Nintendo", "Playtika");
    collection_free(software);
    software = collection_from_array(9, "Apple", "Microsoft", "Oracle", "Google", "Sap", "PayPal", "Playtika", "Amdocs", "OpenAI");
    collection_free(hardware);
    hardware = collection_from_array(8, "Apple", "Nice", "Sony", "Google", "Cummins", "Nucor", "Microsoft", "Nvidia");
    collection_free(industrial);
    industrial = collection_from_array(3, "Caterpillar", "Cummins", "Nucor");
    printf("Companies that sell hardware & software:");
    collection_print(collection_intersection(software, hardware));
    printf("\n");

    collection_t *highSW = collection_new();

    collection_free(highSW);
    highSW = collection_intersection(software, highTech);
    if (highSW == software)
    {
        printf("All software companies are high-tech companies:");
        collection_print(highSW);
        printf("\n");
    }
    else
    {
        printf("Not all software companies are high-tech companies:");
        collection_print(highSW);
        printf("\n");
    }
    collection_add(highSW, "Playtika");
    if (highSW == software)
    {
        printf("Now all software companies are high-tech companies:");
        collection_print(highSW);
        printf("\n");
    }
    else
    {
        printf("Not all software companies are high-tech companies:");
        collection_print(highSW);
        printf("\n");
    }
    printf("Companies that do software or hardware:");
    collection_print(collection_union(software, hardware));
    printf("\n");

    if (collection_intersection(industrial, software) == collection_new())
    {
        printf("No industrial companies sell software");
        printf("\n");
    }
    printf("Companies that sell Hardware but not Gaming Software:");
    collection_print(collection_difference(hardware, (collection_intersection(software, gaming))));
    printf("\n");

    // Cleanup
    collection_free(software);
    collection_free(highTech);
    collection_free(gaming);
    collection_free(hardware);
    collection_free(industrial);
    collection_free(highSW);
    return 0;
}
