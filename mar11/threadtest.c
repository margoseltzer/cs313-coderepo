#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024
#define NUMITER 10

/*
 * The basic idea here is to show that the threads are sharing the
 * fd and therefore the offset. BUT -- there is a race condition
 * where thread1 might read offset 1024, but before it can print
 * that offset, thread2 runs and changes the offset. The sleep
 * mostly gets around this, but not entirely!
 */

/* Make fd global, so the threads can use it. */
int fd;

void *
threadFunc(void *arg) {
	char buf[BUFSIZE];
	ssize_t nbytes;
	int me = *(int *)arg;

	for (int i = 0; i < NUMITER; i++) {
		sleep(1);
		nbytes = read(fd, buf, BUFSIZE);
		if (nbytes < 0) {
			fprintf(stderr, "Read failed: %s\n", strerror(errno));
			(void)close(fd);
			exit(1);
		} else if (nbytes < BUFSIZE) {
			fprintf(stderr, "Short read expected %d got %zd\n", BUFSIZE, nbytes);
		}
		/* Call lseek to get current offset. */
		printf("Thread %d: Offset is %" PRIuMAX "\n", me, (uintmax_t)lseek(fd, 0, SEEK_CUR));
	}
	return NULL;
}

int
main(int argc, char *argv[]) {
	pthread_t t1, t2;

	/* Open the fd once and use in the two threads. */
	fd = open("/bin/ksh", O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "Open failed %s\n", strerror(errno));
		exit(1);
	}

	int id1 = 1;
	pthread_create(&t1, NULL, threadFunc, &id1);
	int id2 = 2;
	pthread_create(&t2, NULL, threadFunc, &id2);
	(void)pthread_join(t1, NULL);
	(void)pthread_join(t2, NULL);
	(void)close(fd);
	exit(0);
}

