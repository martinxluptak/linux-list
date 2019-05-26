#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SKIPLIST_MAX_LEVEL 6

typedef struct snode {
    int key;
    int value;
    struct snode **forward;
} snode;

typedef struct skiplist {
    int level;
    struct snode *header;
} skiplist;

bool skiplist_init(skiplist *list)
{
    int i;
    snode *header = malloc(sizeof(struct snode));
    if (!header)
        return false;
    header->forward = malloc(sizeof(snode *) * (SKIPLIST_MAX_LEVEL + 1));
    if (!header->forward) {
        free(header);
        return false;
    }
    list->header = header;
    header->key = INT_MAX;
    for (i = 0; i <= SKIPLIST_MAX_LEVEL; i++) {
        header->forward[i] = list->header;
    }

    list->level = 1;

    return true;
}

static int rand_level()
{
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL)
        level++;
    return level;
}

int skiplist_insert(skiplist *list, int key, int value)
{
    snode *update[SKIPLIST_MAX_LEVEL + 1];
    snode *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward[1];

    /* update element if key is found */
    if (key == x->key) {
        x->value = value;
        return 1;
    }

    /* insert new element - first pick a random level */
    level = rand_level();
    if (level > list->level) {
        for (i = list->level + 1; i <= level; i++) {
            update[i] = list->header;
        }
        list->level = level;
    }

    /* create a new node for inserted element */
    x = malloc(sizeof(snode));
    if (!x)
        return -1;
    x->key = key;
    x->value = value;

    /* link the node appriopriately */
    x->forward = malloc(sizeof(snode *) * (level + 1));
    if (!x->forward)
        return -1;
    for (i = 1; i <= level; i++) {
        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x;
    }
    return 1;
}

snode *skiplist_search(skiplist *list, int key)
{
    snode *x = list->header;
    int i;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
    }
    if (x->forward[1]->key == key) {
        return x->forward[1];
    } else {
        return NULL;
    }
    return NULL;
}

static void skiplist_node_free(snode *x)
{
    if (x) {
        free(x->forward);
        free(x);
    }
}

int skiplist_delete(skiplist *list, int key)
{
    int i;
    snode *update[SKIPLIST_MAX_LEVEL + 1];
    snode *x = list->header;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }

    x = x->forward[1];
    if (x->key == key) {
        for (i = 1; i <= list->level; i++) {
            if (update[i]->forward[i] != x)
                break;
            update[i]->forward[i] = x->forward[i];
        }
        skiplist_node_free(x);

        while (list->level > 1 &&
               list->header->forward[list->level] == list->header)
            list->level--;
        return 0;
    }
    return 1;
}

void skiplist_free(skiplist *list)
{
    snode *current_node = list->header->forward[1];
    while (current_node != list->header) {
        snode *next_node = current_node->forward[1];
        free(current_node->forward);
        free(current_node);
        current_node = next_node;
    }
    free(current_node->forward);
    free(current_node);
}

static void skiplist_dump(skiplist *list)
{
    snode *x = list->header;
    while (x && x->forward[1] != list->header) {
        printf("%d[%d]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }
    printf("NIL\n");
}
