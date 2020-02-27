#include "matrixincludes.h"
#define MELT(matrix, sz, row, col) (matrix)[(row) * (sz) + (col)]

void square_matrix_multiply(double* c, const double* a, const double* b,
			    size_t sz) {
    for (size_t i = 0; i < sz; ++i)
        for (size_t j = 0; j < sz; ++j)
            MELT(c, sz, i, j) = 0;
    for (size_t i = 0; i < sz; ++i)
	for (size_t j = 0; j < sz; ++j)
	    for (size_t k = 0; k < sz; ++k)
		MELT(c, sz, i, j) += MELT(a, sz, i, k) * MELT(b, sz, k, j);
}

#include "matrixmultiply-main.c"
