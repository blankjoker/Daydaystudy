/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：fork.c
*   创 建 者：zhangkunliang
*   创建日期：2020年10月21日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>

int main(void)  
{  
	pid_t pid = fork();  
	if (pid == 0) {  
		int j ;  
		for (j = 0; j < 10; j++) {  
			printf("child: %d\n", j);  
			sleep(3);  
		}  
	}  
	else if (pid > 0) {
		int i;  
		for (i = 0; i < 10; i++)  
		{  
			printf("parent: %d\n", i);  
			sleep(1);  
		}  
	}
	else {  
		fprintf(stderr, "can't fork ,error %d\n", errno);  
		exit(1);  
	}  
	printf("This is the end !");  
}
