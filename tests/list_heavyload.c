#include <time.h>
#include "list.h"

#include "common.h"

#define LIST_SIZE 10000
#define MAX_NUMBER 100000
#define SEARCH_COUNT 100000

int main()
{
    uint32_t i;
    struct list_head list;
    int *arr;
    INIT_LIST_HEAD(&list);
    clock_t start, end;
    double cpu_time_used;

    arr = malloc(LIST_SIZE * sizeof(int));

    start = clock();
    /* put elements into list */
    for (i = 0; i < LIST_SIZE; i++) {
        int new = rand() % MAX_NUMBER;
        arr[i] = new;
        struct listitem *i = malloc(sizeof(struct listitem));
        list_add(&i->list, &list);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time inserting in list:%f\n", cpu_time_used);

    start = clock();
    /* search for random list element */
    for (i = 0; i < SEARCH_COUNT; i++) {
        int search = arr[rand() % LIST_SIZE];
        list_contains(&list, search);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time searching in list:%f\n", cpu_time_used);
    free(arr);
    return 0;
}
