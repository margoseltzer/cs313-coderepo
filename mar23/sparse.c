#include <fcntl.h>
#include <unistd.h>

/* Bad error handling! */
int
main(int argc, char *argv[]) {
	int fd = open("myfile", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	char c = 'a';
	(void) write(fd, &c, 1);
	(void) lseek(fd, 1000000, SEEK_CUR);
	(void) write(fd, &c, 1);
	(void)close(fd);
}
