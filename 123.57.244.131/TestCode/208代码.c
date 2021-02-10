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

int main(void)
{
	pid_t result;

	result = fork();

	if(result == -1)
	{
		printf("Fork error\n");
	}
	else if(result == 0)
	{
		printf("The returned value is %d \n In child process!!\nMy PID is %d\n", result, getpid());
	}
	else
	{
		printf("The returned value is %d \n In father process!!\nMy PID is %d\n", result, getpid());
	}
	return result;
}