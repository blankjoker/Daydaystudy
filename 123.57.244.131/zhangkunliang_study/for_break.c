

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int count = 5;
	int i = 1;
	for (i; i < count; i++) {
		if (i == 3) {
			break;
		}
		printf(">>>>>>>>>>:%d\n", i);
	}
	return 0;
}