#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd, flags, numWritten;

	flags = O_RDWR | O_CREAT;

	fd = open("test.txt",  flags);
	if (fd == -1)
		printf("open file failed\n");

	numWritten = write(fd, "Hello\n", 10);
	if (numWritten == -1 )
		printf("write \"hell\" failed\n");

	numWritten = write(fd, "world\n", 10);
	if (numWritten == -1)
		printf("write \"world\" failed\n");

	flags = fcntl(fd, F_GETFD);
	if (flags == -1)
		printf("get model failed\n");

	flags |= O_APPEND;
	if (fcntl(fd, F_SETFD, flags) == -1)
		printf("set model failed\n");

	close(fd);

	exit(EXIT_SUCCESS);
}
