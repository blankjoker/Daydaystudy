

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char str[1048576] = { 0 };
	memset(str, 'c', 1048576);
	printf(">>>>>>>>>>>>>>>%s\n", str);

	return 0;
}