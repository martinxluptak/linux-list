#ifndef PRIVATE_COMMON_H
#define PRIVATE_COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

typedef struct listitem {
    uint16_t i;
    struct list_head list;
} item_t;

typedef struct list_head head;

static inline uint8_t getnum(void)
{
    static uint16_t s1 = UINT16_C(2);
    static uint16_t s2 = UINT16_C(1);
    static uint16_t s3 = UINT16_C(1);

    s1 *= UINT16_C(171);
    s1 %= UINT16_C(30269);

    s2 *= UINT16_C(172);
    s2 %= UINT16_C(30307);

    s3 *= UINT16_C(170);
    s3 %= UINT16_C(30323);

    return s1 ^ s2 ^ s3;
}

static uint16_t get_unsigned16(void)
{
    uint16_t x = 0;
    size_t i;

    for (i = 0; i < sizeof(x); i++) {
        x <<= 8;
        x |= getnum();
    }

    return x;
}

static inline int cmpint(const void *p1, const void *p2)
{
    const uint16_t *i1 = (const uint16_t *) p1;
    const uint16_t *i2 = (const uint16_t *) p2;

    return *i1 - *i2;
}

static inline void random_shuffle_array(uint16_t *operations, uint16_t len)
{
    uint16_t i;
    uint16_t j;

    for (i = 0; i < len; i++) {
        /* WARNING biased shuffling */
        j = get_unsigned16() % (i + 1);
        operations[i] = operations[j];
        operations[j] = i;
    }
}

static inline item_t *create_random_item()
{
    item_t *newitem = malloc(sizeof(newitem));
    newitem->i = get_unsigned16();
    return newitem;
}

static inline void add_random_items(struct list_head *h, uint16_t howmany)
{
    while (howmany--) {
        item_t *newitem = create_random_item();
        list_add(&newitem->list, h);
    }
}

static inline int compare_listitem(head *a, head *b)
{
    item_t *t, *u;
    t = list_entry(a, item_t, list);
    u = list_entry(b, item_t, list);
    return cmpint((void *) &t->i, (void *) &u->i);
}

static inline void print_item(head *h)
{
    item_t *t = list_entry(h, item_t, list);
    printf("%d", t->i);
}

static inline void print_list(head *h)
{
    item_t *t;
    list_for_each_entry (t, h, list) {
        printf("%d,", t->i);
    }
    printf("\n");
}

static inline void free_list(head *h)
{
    item_t *t;
    list_for_each_entry (t, h, list) {
        free(t);
    }
    free(h);
}

static inline int list_size(head *h)
{
    int cnt = 0;
    head *next = h->next;
    while (next != h) {
        next = next->next;
        cnt++;
    }
    return cnt;
}

static inline bool list_contains(head *h, uint16_t element)
{
    item_t *t;
    list_for_each_entry (t, h, list) {
        if (t->i == element)
            return true;
    }
    return false;
}

#endif /* PRIVATE_COMMON_H */
