#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "numwave.h"

struct vector {
    unsigned size;
    unsigned capacity;
    value_t* data;
};

static inline void
vector_grow(struct vector* v)
{
    unsigned new_capacity;
    value_t *new_data;
    
    new_capacity = (v->capacity ? v->capacity * 2 : 16);
    new_data = (value_t *)realloc(v->data, sizeof(value_t) * new_capacity);
    if (new_data != NULL)
        v->data = new_data;
    v->capacity = new_capacity;
}

/* Unsorted fast vector add (place value at end). */
void *
vector_add_fast(void *vv, value_t value) 
{
    struct vector *v;

    v = vv;
    if (v->size == v->capacity)
        vector_grow(v);
    v->data[v->size] = value;
    v->size++;
    return (v);
}

/* Unsorted, but place new element at the beginning. */
void *
vector_add_first(void *vv, value_t value) 
{
    struct vector *v;

    v = vv;
    if (v->size == v->capacity)
        vector_grow(v);

    memmove(&v->data[0], &v->data[1], sizeof(value_t) * (v->size));
    v->data[0] = value;
    v->size++;
    return (v);
}

void *
vector_add_sorted(void *vv, value_t value)
{
    struct vector *v;
    unsigned position;
    
    v = vv;
    position = 0;
    while (position != v->size && v->data[position] < value)
        position++;

    if (v->size == v->capacity)
        vector_grow(v);

    memmove(&v->data[position + 1], &v->data[position],
	    sizeof(value_t) * (v->size - position));
    v->data[position] = value;
    v->size++;

    return (v);
}

/* Remove first. */
void *
vector_remove_first(void *vv, unsigned position)
{
    struct vector *v;

    v = vv;
    v->size--;
    memmove(&v->data[1], &v->data[0], sizeof(value_t) * (v->size));
    return (v);
}

/* Remove last. */
void *vector_remove_last(void *vv, unsigned position)
{
    struct vector *v;

    v = vv;
    v->size--;
    return (v);
}

/* Sorted remove. */
void *
vector_remove(void *vv, unsigned position)
{
    unsigned cur_position;
    struct vector *v;
    
    v = vv;
    for (cur_position = 0; cur_position != position; ++cur_position);

    assert (cur_position < v->size);

    memmove(&v->data[cur_position], &v->data[cur_position + 1],
	    sizeof(value_t) * (v->size - cur_position - 1));
    v->size--;
    return (v);
}

void *
vector_init(struct optable *ops, unsigned flags)
{
    struct vector *v;

    v = (struct vector *)malloc(sizeof(struct vector));
    if (v != NULL) {
        v->data = NULL;
        v->capacity = 0;
        v->size = 0;
    }
    if (flags & F_SORT) {
        ops->add = vector_add_sorted;
        ops->remove = vector_remove;
    } else if (flags * F_FASTVECTOR) {
        ops->add = vector_add_fast;
        ops->remove = vector_remove_last;
    } else {
        ops->add = vector_add_first;
        ops->remove = vector_remove_first;
    }
    return (v);
}


