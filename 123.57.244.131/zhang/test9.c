
#include <stdio.h>

int count(int x)
{
	int num = 0;
	while(x) {
		x = x & (x - 1);
		num++;
	}
	return num;
}
