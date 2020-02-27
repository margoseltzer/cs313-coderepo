#include <assert.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "matrixincludes.h"
#define MELT(matrix, sz, row, col) (matrix)[(row) * (sz) + (col)]
#define tv_ms_diff(tv1, tv2) \
        (tv2.tv_sec * 1000) + ((double)tv2.tv_usec / 1000) - \
        ((tv1.tv_sec * 1000) + ((double)tv1.tv_usec / 1000))

void square_matrix_multiply(double* c, const double* a, const double* b,
			    size_t sz) {
    struct timeval tv_begin, tv_end;
    struct rusage usage_begin, usage_end;

    for (size_t i = 0; i < sz; ++i)
        for (size_t j = 0; j < sz; ++j)
            MELT(c, sz, i, j) = 0;
    
    int r = getrusage(RUSAGE_SELF, &usage_begin);
    assert (r >= 0);
    r = gettimeofday(&tv_begin, 0);
    assert(r >= 0);

    // Here is the Matrix Multiply
    for (size_t i = 0; i < sz; ++i)
	for (size_t j = 0; j < sz; ++j)
	    for (size_t k = 0; k < sz; ++k)
		MELT(c, sz, i, j) += MELT(a, sz, i, k) * MELT(b, sz, k, j);

    r = gettimeofday(&tv_end, 0);
    assert (r >= 0);
    r = getrusage(RUSAGE_SELF, &usage_end);
    assert (r >= 0);

    // Compute elapsed time in ms
    printf("Elapsed time (ms): %7.2f\n", tv_ms_diff(tv_begin, tv_end));
    printf("User time (ms)   : %7.2f\n",
        tv_ms_diff(usage_begin.ru_utime, usage_end.ru_utime));
    printf("System time (ms) : %7.2f\n",
        tv_ms_diff(usage_begin.ru_stime, usage_end.ru_stime));
}

#include "matrixmultiply-main.c"
