#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char *argv[]) {
	int fd1 = open("/bin/ksh", O_RDONLY);
	if (fd1 < 0) {
		fprintf(stderr, "First open failed %s\n", strerror(errno));
		exit(1);
	}

	int fd2 = open("/bin/ksh", O_RDONLY);
	if (fd2 < 0) {
		fprintf(stderr, "Second open failed %s\n", strerror(errno));
		exit(1);
	}

	printf("fd1 = %d fd2 = %d\n", fd1, fd2);
	(void)close(fd1);
	(void)close(fd2);
	exit(0);
}
