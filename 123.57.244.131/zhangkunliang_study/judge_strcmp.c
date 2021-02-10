

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	/* code */
	char buf1[10] = "sss";
	char buf2[4] = "sss";
	if (0 == strcmp(buf1, buf2)) {
		printf("ssssssssssssssssssssss\n");
	}
	return 0;
}