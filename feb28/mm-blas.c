#include "matrixincludes.h"
#include <cblas.h>
#define MELT(matrix, sz, row, col) (matrix)[(row) * (sz) + (col)]

void square_matrix_multiply(double* c, const double* a, const double* b,
			    size_t sz) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                sz, sz, sz,
                1.0, a, sz, b, sz,
                0.0, c, sz);
}

#include "matrixmultiply-main.c"
