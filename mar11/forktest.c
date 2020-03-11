#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024
#define NUMITER 10

/*
 * We're going to create a child process and see how the parent/
 * child share file descriptors.
 */

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

	/* Now, fork off a child. */
	pid_t pid = fork();

	if (pid == 0) {
		/* I am the child process. */
		me = "Child";
	} else if (pid < 0) {
		fprintf(stderr, "Fork failed %s\n", strerror(errno));
		exit(1);
	} else {
		/* I am the parent process. */
		me = "Parent";
	}

	for (int i = 0; i < NUMITER; i++) {
		nbytes = read(fd, buf, BUFSIZE);
		if (nbytes < 0) {
			fprintf(stderr, "%s: Read failed: %s\n", me, strerror(errno));
			(void)close(fd);
			exit(1);
		} else if (nbytes < BUFSIZE) {
			fprintf(stderr, "%s: Short read expected %d got %zd\n", me, BUFSIZE, nbytes);
		}
		/* Call lseek to get current offset. */
		printf("%s: Offset is %lld\n", me, lseek(fd, 0, SEEK_CUR));
		sleep(1);
	}
	if (close(fd) != 0) {
		fprintf(stderr, "%s: Close failed: %s\n", me, strerror(errno));
	}
	exit(0);
}
