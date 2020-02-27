#include <assert.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include "numwave.h"

int
usage()
{
    fprintf(stderr, "usage: ./numwave [-f [sort|fast|addonly] %s\n",
        "[-n count] [-p pad] [-t [list|vector]]");
    return (-1);
}

int
main(int argc, char *argv[])
{
    extern int optind;
    char ch, *type;
    unsigned long count, flags;
    struct optable ops;
    void *data;

    /* Default values; can be overridden by command line. */
    count = 10000;
    type = "list";
    flags = 0;

    /* Command line processing. */
    while ((ch = getopt(argc, argv, "f:n:p:t:")) != EOF)
	switch (ch) {
        case 'f':
            if (strcmp(optarg, "sort") == 0)
                flags |= F_SORT;
            else if (strcmp(optarg, "fast") == 0)
                flags |= F_FASTVECTOR;
            else if (strcmp(optarg, "addonly") == 0)
                flags |= F_ADDONLY;
            break;
	    case 'n':
            count = strtoul(optarg, 0, 0);
            break;
        case 'p':
            list_pad = (size_t) strtoul(optarg, 0, 0);
            break;
	    case 't':
		    type = optarg;
            break;
	    case '?':
	    default:
		    return (usage());
	}

    argc -= optind;
    argv += optind;

    if (strcmp(type, "list") == 0)
        data = list_init(&ops, flags);
    else if (strcmp(type, "vector") == 0)
        data = vector_init(&ops, flags);
    else
        return (usage());

    for (unsigned long i = 0; i < count; ++i)
	    data = ops.add(data, random());
    if ((flags & F_ADDONLY) == 0)
        for (unsigned long i = count; i > 0; --i)
            data = ops.remove(data, random() % i);

    return (0);
}

