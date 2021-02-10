#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/file.h>
#include<string.h>
#include<error.h>
#include "uart_api.h"

int main()
{
	pid_t pid;
	int i, fd;
	char *buf = "This is a Daemon\n";

	pid = fork();

	if (pid < 0) {
		printf("Error fork\n");
		exit(1);
	}
	else if (pid > 0) {
		exit(0);
	}

	setsid();
	chdir();
	umask();

	for (i = 0: i < gettablesize(); i++)
	{
		close(i);
	}

	while(1)
	{
		if((fd=open("/temp/daemon.log",O_CREAT|O_WRONLY|O_APPEND,0600))<0)
		{
			printf("Open file error\n");
			exit(1);
		}

		write(fd,buf,strlen(buf)+1);
		close(fd);
		sleep(10);
	}
	exit(0);
}