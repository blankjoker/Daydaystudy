
#include <stdio.h>

#define CHAR char*

int main(int argc, char const *argv[])
{
	/* code */
	char *aa, *bb;
	char buf[] = "ssssssssss";
	aa = buf;
	bb = buf;
	printf(">>>>>>>>>>>>>>>>>>>%s\n", aa);
	printf(">>>>>>>>>>>>>>>>>>>%s\n", bb);

	return 0;
}