#include <stdint.h>
#include "skiplist.h"

int main()
{
    int arr[] = {3, 6, 9, 2, 11, 1, 4};
    uint32_t i;
    skiplist list;
    if (!skiplist_init(&list))
        return -1;

    printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        skiplist_insert(&list, arr[i], arr[i]);
    }
    skiplist_dump(&list);

    printf("Search:--------------------\n");
    int keys[] = {3, 4, 7, 10, 111};

    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        snode *x = skiplist_search(&list, keys[i]);
        if (x) {
            printf("key = %d, value = %d\n", keys[i], x->value);
        } else {
            printf("key = %d, not found\n", keys[i]);
        }
    }

    printf("Search:--------------------\n");
    skiplist_delete(&list, 3);
    skiplist_delete(&list, 9);
    skiplist_dump(&list);

    return 0;
}
