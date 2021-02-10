
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	// char str[1024] = "<0x01><0x02>";
	// printf(">>>>>>>>>>>>>>>:%s\n", str);
	char buf[10];
	memset(buf, 0, 10);
	printf("222222222222222:%d\n", strlen(buf));
	printf("22222222222222:%p\n", buf);
	// memset(buf, 0, 10);
	if (0 == strlen(buf)) {
		printf("ssssssssssssssssssssssssssss\n");
	}
	else {
		
		printf("11111111111111111111111\n");
	}
	return 0;
}

