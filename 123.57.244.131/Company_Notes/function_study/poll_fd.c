/*===============================================================
*   Copyright (C) 2018 All rights reserved.
*   
*   文件名称：select.c
*   创 建 者：liujing
*   创建日期：2018年07月09日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>

int main()
{
	int fd = open("/dev/input/mouse1", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}

	struct pollfd fds[2];//建立一个关于文件描述符的集合
	fds[0].fd = 0;//把0添加到集合fds中，0表示标准输入
	fds[0].events = POLLIN;   //监测是否有数据可读
	fds[1].fd = fd;
	fds[1].events = POLLIN;
	
	int retval;
	char buf[100];
	while (1)
	{
		retval = poll(fds, 2, 1000); //监听事件
		if (retval < 0)
		{
			perror("select");
			break;
		}
		else if (0 == retval)
		{
			printf("timeout.......\n");
			continue;
		}
		
		if (fds[0].revents & POLLIN)   //判断是否是0产生事件
		{
			read(0, buf, sizeof(buf));  //把缓冲区内容读取出来
			printf("Data from keyboard!\n");
		}
		if (fds[1].revents & POLLIN)
		{
			read(fd, buf, sizeof(buf));
			printf("Data from mouse!\n");
		}
	}
	close(fd);

	return 0;
}
