#include <fcntl.h>
#include <unistd.h>

/* Bad error handling! */
int
main(int argc, char *argv[]) {
	int fd = open("tinyfile", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	char c = 'a';
	(void) write(fd, &c, 1);
	(void)close(fd);
}
