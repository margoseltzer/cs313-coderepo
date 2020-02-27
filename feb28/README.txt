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

mm-blas: Uses the blas library to give a good target to shoot for in improving
the performance of mm-ijk.

numwave.c: This program is highly configurable and demonstrates that while
linked lists are simple; they are not terribly efficient.  Command line
options are:
    -f flags, one of:
        sort: maintain entries in sorted order (this is the most useful one)
        addonly: stop the test after adding the entries rather than adding
            and removing.
        fast: an unsorted test: adds/removes elements at the end of the
            vector rather than at the beginning
        default is: unsorted where both vector and list add/remove the
            first element -- greatly benefiting the linked list.
    -n number of elements to add/remove to the structure
    -p (pad) number of bytes to pad linked list structures (intended to 
        demonstrate what happens when you consume multiple cache lines, but
        without writing to them, doesn't have much effect and I didn't want
        to write to them, because that's just 'busy work'
    -t (type), one of list or vector

