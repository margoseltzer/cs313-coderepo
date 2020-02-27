This directory contains a set of programs to let you observe how much
hardware caching can effect performance.

We begin with layout.c: This framework provides practice programming with
2D arrays and figuring out how they are laid out in memory.

Next comes layout-row.c and layout-column.c: These are designed to let
you compare the performance of traversing a 3D array by rows and
columns to see how memory access patterns affect performance.

mm-ijk: This is a simple nested loop implementation of a square matrix
multiply. We ask that you reorder the loops to achieve better performance
due to the efficacy of the hardware cache.
