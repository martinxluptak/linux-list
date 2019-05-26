#include <assert.h>
#include <stdlib.h>
#include "list.h"

#include "common.h"

int main(void)
{
    head *testlist = malloc(sizeof(head));

    INIT_LIST_HEAD(testlist);
    assert(list_empty(testlist));

    add_random_items(testlist, 100);
    assert(list_size(testlist) == 100);

    int i = 100;
    while (--i) {
        list_pop(testlist);
        assert(list_size(testlist) == i);
    }

    free_list(testlist);
    return 0;
}
