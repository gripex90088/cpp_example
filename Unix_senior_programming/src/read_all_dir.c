// read_all_dir.c  read all file form parameter directory 从目录参数中读取所有文件
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char * argv[])
{
	DIR *dp;
	struct dirent *dirp;

	if (argc != 2)
		printf("a single argument (the directory name) is required");

	if ((dp = opendir(argv[1])) == NULL)
		printf("can't open %s", argv[1]);

	while((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);

	closedir(dp);
	exit(EXIT_SUCCESS);
}
