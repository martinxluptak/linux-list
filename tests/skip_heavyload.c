#include <stdint.h>
#include <time.h>
#include "skiplist.h"

#define SKIPLIST_SIZE 10000
#define MAX_NUMBER 100000
#define SEARCH_COUNT 100000

int main()
{
    uint32_t i;
    skiplist list;
    int *arr;
    clock_t start, end;
    double cpu_time_used;
    if (!skiplist_init(&list))
        return -1;

    arr = malloc(SKIPLIST_SIZE * sizeof(int));
    skiplist_dump(&list);

    start = clock();
    /* put elements into skiplist */
    for (i = 0; i < SKIPLIST_SIZE; i++) {
        int new = rand() % MAX_NUMBER;
        arr[i] = new;
        skiplist_insert(&list, new, new);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time inserting in skiplist:%f\n", cpu_time_used);

    start = clock();
    /* search for random skiplist element */
    for (i = 0; i < SEARCH_COUNT; i++) {
        int search = arr[rand() % SKIPLIST_SIZE];
        skiplist_search(&list, search);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time searching in skiplist:%f\n", cpu_time_used);

    skiplist_free(&list);
    free(arr);
    return 0;
}
