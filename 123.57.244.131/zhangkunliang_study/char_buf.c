

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char buf[20] = { "sss" };
	// strcpy(buf, "sssssssssssssssssssssssssssss");
	printf(">>>>>>>>>>>>>>%s\n", buf);
	printf(">>>>>>>>>>>>>>%c\n", buf[0]);
	printf(">>>>>>>>>>>>>>%c\n", buf[1]);
	return 0;
}