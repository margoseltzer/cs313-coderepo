#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "numwave.h"

/* Global to hold amount to pad linked list structures. */
size_t list_pad;

struct link {
    value_t value;
    struct link* next;
};

static inline struct link* list_alloc(void)
{
    return (struct link*) malloc(sizeof(struct link) + list_pad);
}

static inline void list_free(struct link *link)
{
    free(link);
}

/* Unsorted add. */
void *
list_add(void *vlist, value_t value)
{
    struct link *list, *newlink;

    list = vlist;

    newlink = list_alloc();
    newlink->value = value;
    newlink->next = list;
    return (newlink);
}

/* Sorted add. */
void *
list_sorted_add(void *vlist, value_t value) {
    struct link *first, *list, *newlink, *prev;

    list = vlist;
    first = list;
    prev = NULL;
    while (list && list->value < value) {
        prev = list;
        list = list->next;
    }

    newlink = list_alloc();
    newlink->value = value;
    newlink->next = list;
    if (prev == NULL)
        first = newlink;
    else
        prev->next = newlink;
    return (first);
}

/* Remove first element. */
void *
list_remove_first(void *vlist, unsigned position)
{
    struct link *list;

    list = vlist;
    list = list->next;
    list_free ((struct link *)vlist);
    return (list);
}

/* Remove element in the Nth position. */
void *
list_remove_pos(void *vlist, unsigned position)
{
    struct link *list, *prev, *first;

    list = vlist;
    prev = NULL;
    first = list;
    while (position > 0) {
        prev = list;
        list = list->next;
        --position;
    }
    assert(list != NULL);
    if (prev != NULL)
        prev->next = list->next;
    else
        first = list->next;
    list_free(list);
    return (first);
}


void *
list_init(struct optable *ops, unsigned flags)
{
    if ((flags & F_SORT) != 0) {
        ops->add = list_sorted_add;
        ops->remove = list_remove_pos;
    } else {
        ops->add = list_add;
        ops->remove = list_remove_first;
    }
    return (NULL);
}
