#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/file.h>
#include "lock_set.c"

int main()
{
	int fd;

	fd = open("hello", O_RDWR|O_CREAT, 0644);

	if(fd < 0)
	{
		printf("Open file error\n");
		exit(1);
	}

	lock_set(fd, F_WRLCK);
	getchar();

	lock_set(fd, F_UNLCK);
	getchar();
	close(fd);
	exit(0);
}