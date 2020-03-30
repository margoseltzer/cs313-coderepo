#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

int
main(int argc, char *argv[]) {
	char buf[BUFSIZE];
	ssize_t nbytes;

	int fd1 = open("/bin/ksh", O_RDONLY);
	if (fd1 < 0) {
		fprintf(stderr, "First open failed %s\n", strerror(errno));
		exit(1);
	}

	int fd2 = dup(fd1);
	if (fd2 < 0) {
		fprintf(stderr, "Second open failed %s\n", strerror(errno));
		exit(1);
	}

	printf("fd1 = %d fd2 = %d\n", fd1, fd2);

	for (int i = 0; i < 10; i++) {
		nbytes = read(fd1, buf, BUFSIZE);
		if (nbytes < 0) {
			fprintf(stderr, "Read of fd1 failed: %s\n", strerror(errno));
			(void)close(fd1);
			exit(1);
		} else if (nbytes < BUFSIZE) {
			fprintf(stderr, "Short read of fd1 expected %d got %zd\n", BUFSIZE, nbytes);
		}
		/* Call lseek to get current offset. */
		printf("Offset of fd1 is %" PRIuMAX "\n", (uintmax_t)lseek(fd1, 0, SEEK_CUR));

		nbytes = read(fd2, buf, BUFSIZE);
		if (nbytes < 0) {
			fprintf(stderr, "Read of fd2 failed: %s\n", strerror(errno));
			(void)close(fd2);
			exit(1);
		} else if (nbytes < BUFSIZE) {
			fprintf(stderr, "Short read of fd2 expected %d got %zd\n", BUFSIZE, nbytes);
		}
		/* Call lseek to get current offset. */
		printf("Offset of fd2 is %" PRIuMAX "\n", (uintmax_t)lseek(fd2, 0, SEEK_CUR));
	}

	(void)close(fd1);
	(void)close(fd2);
	exit(0);
}
