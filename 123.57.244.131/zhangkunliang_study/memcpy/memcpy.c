

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	/* code */
	int a = 2018;
	int b = 0;
	memcpy(&b, &a, 1);
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	return 0;
}