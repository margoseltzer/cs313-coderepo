#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

/* Bad error handling! */
int
main(int argc, char *argv[]) {
	char buf[4096];
	int fd = open("analyzefile", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	for (int i = 0; i < 100; i++) {
		struct stat statbuf;
		(void) write(fd, buf, 4096);

		fstat(fd, &statbuf);
		if (statbuf.st_size / 512 != statbuf.st_blocks) {
			printf("File size: %lld\n", statbuf.st_size);
			printf("Block count: %lld\n", statbuf.st_blocks);
			printf("Block size: %d\n", statbuf.st_blksize);
		}
	}
	(void)close(fd);
}
