#include <stdlib.h>

#define F_SORT          0x01
#define F_ADDONLY       0x02
#define F_FASTVECTOR    0x04

typedef unsigned value_t;
typedef unsigned bool;

/*
 * We will use a function dispatch table so that the program will work
 * with a variety of different data structures.  Each data structure provides
 * an initialization routine that takes some flags to indicate if the
 * structure is sorted and then assigns the appropriate operation.
 */
struct optable {
    void *(* add)(void *, value_t);
    void *(* remove)(void *, unsigned);
};

void *list_init(struct optable *, unsigned);
void *vector_init(struct optable *, unsigned);

extern size_t list_pad;
