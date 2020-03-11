#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024
#define NUMITER 100

int
main(int argc, char *argv[]) {
	char buf[BUFSIZE];
	char *me;
	ssize_t nbytes;

	int fd = open("/bin/ksh", O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "Open failed %s\n", strerror(errno));
		exit(1);
	}

	for (int i = 0; i < NUMITER; i++) {
		nbytes = read(fd, buf, BUFSIZE);
		if (nbytes < 0) {
			fprintf(stderr, "Read failed: %s\n", strerror(errno));
			(void)close(fd);
			exit(1);
		} else if (nbytes < BUFSIZE) {
			fprintf(stderr, "Short read expected %d got %zd\n", BUFSIZE, nbytes);
		}
		/* Call lseek to get current offset. */
		printf("Offset is %lld\n", lseek(fd, 0, SEEK_CUR));
	}
	(void)close(fd);
	exit(0);
}
