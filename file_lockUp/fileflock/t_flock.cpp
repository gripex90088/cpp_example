/*
 * t_flock.c
 * Linux-UNIX系统编程手册（上、下册）.pdf, chapter 55-1
 *
 *  Created on: Jul 24, 2019
 *      Author: xuxing
 */

#include <iostream>
#include <sys/file.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctime>

char * currTime()
{
	time_t a = time(0);
	return asctime(localtime(&a));
}

int main(int argc, char * argv[])
{
	int fd, lock;
	const char *lname;

	if (argc < 3 || strcmp(argv[1], "--help") == 0 ||
			strchr("sx", argv[2][0]) == NULL)
		printf("%s file lock [sleep-time]\n"
				"   'lock' is 's' (shared) or 'x' (exclusive)\n"
				"		optionally followed by 'n' (nonblocking)\n"
				"	'secs' specifies time to hold lock\n", argv[0]);

	lock = (argv[2][0] == 's') ? LOCK_SH : LOCK_EX;
	if (argv[2][1] == 'n')
		lock |= LOCK_NB;

	fd = open(argv[1], O_RDONLY); /* open file to be locked */
	if (fd == -1)
	{
		printf("open file filed\n");
		exit(EXIT_FAILURE);
	}

	lname = (lock & LOCK_SH) ? "LOCK_SH" : "LOCK_EX";

	printf("PID %ld: requesting %s at %s\n", (long)getpid(), lname, currTime());

	if (flock(fd, lock) == -1)
	{
		if (errno == EWOULDBLOCK)
		{
			printf("PID %ld: already locked - bye!", (long) getpid());
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("flock (PID=%ld)", (long)getpid());
			exit(EXIT_FAILURE);
		}
	}

	printf("PID %ld:  granted	%s at %s\n", (long)getpid(),lname,currTime());

	sleep(60);
	printf("PID %ld: releasing %s at %s\n", (long)getpid(), lname, currTime());

	if (flock(fd, LOCK_UN) == -1)
	{
		printf("flock unlock falied\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}


