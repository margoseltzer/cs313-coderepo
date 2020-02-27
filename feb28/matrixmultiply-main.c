int main(int argc, char** argv) {
    size_t sz = 1000;
    if (argc >= 2)
	sz = strtoul(argv[1], NULL, 0);
    assert(sz > 0);
    assert(sz < (size_t) sqrt(SIZE_MAX / 4));

    double* ma = (double*) malloc(sizeof(double) * sz * sz);
    for (size_t i = 0; i < sz; ++i)
	for (size_t j = 0; j < sz; ++j)
	    MELT(ma, sz, i, j) = i + (double) j / sz;

    double* mb = (double*) malloc(sizeof(double) * sz * sz);
    for (size_t i = 0; i < sz; ++i)
	for (size_t j = 0; j < sz; ++j)
	    MELT(mb, sz, i, j) = j + (double) i / sz;

    double* mc = (double*) malloc(sizeof(double) * sz * sz);
    square_matrix_multiply(mc, ma, mb, sz);

    printf("c[0, 0] == %g    (%a)\n",
           MELT(mc, sz, 0, 0), MELT(mc, sz, 0, 0));
    printf("c[%zu, %zu] == %g    (%a)\n", sz - 1, sz - 1,
           MELT(mc, sz, sz - 1, sz - 1), MELT(mc, sz, sz - 1, sz - 1));
}
