#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	struct stat statbuf;

	stat("myfile", &statbuf);
	printf("File size: %lld\n", statbuf.st_size);
	printf("Block count: %lld\n", statbuf.st_blocks);
	printf("Block size: %d\n", statbuf.st_blksize);
}
