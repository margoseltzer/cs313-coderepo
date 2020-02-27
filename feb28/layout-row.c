#include <stdio.h>
#define ROWS 5000
#define COLS 10000

void do_something(int);

int array[ROWS][COLS];

int
main(void)
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            do_something(array[i][j]);
    return (0);
}
