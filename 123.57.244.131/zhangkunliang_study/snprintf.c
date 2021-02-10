

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char buf[12];
	int ret = snprintf(buf, 12, "%s", "sss");
	printf(">>>>>>>>>>>>>>>>>>>:%d\n", ret);
	return 0;
}