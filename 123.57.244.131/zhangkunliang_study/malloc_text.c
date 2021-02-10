#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char *buf = (char *)malloc(100);
	memset(buf, 0, 100);
	if (buf != NULL)
	{
		printf("saaaaaaaaaaaaaaaaa\n");
	}
	return 0;
}
