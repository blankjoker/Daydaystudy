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

int main()
{
	int fd = open("/dev/input/mouse1", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}

	fd_set fds, rfds;    //建立一个关于文件描述符的集合
	FD_SET(0, &fds);   //把0添加到集合fds中，0表示标准输入
	FD_SET(fd, &fds);
	
	int retval;
	char buf[100];
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	while (1)
	{
		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		rfds = fds;
		retval = select(fd+1, &rfds, NULL, NULL, &tv); //监听事件
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
		
		if (FD_ISSET(0, &rfds))   //判断是否是0产生事件
		{
			read(0, buf, sizeof(buf));  //把缓冲区内容读取出来
			printf("Data from keyboard!\n");
		}
		if (FD_ISSET(fd, &rfds))
		{
			read(fd, buf, sizeof(buf));
			printf("Data from mouse!\n");
		}
	}
	close(fd);

	return 0;
}
