

#include <stdio.h>
#include "mymain.h"

int count(int x)
{
	int count = 0;
	while(x)
	{
		x = x & (x - 1);
		count++;
	}
	return count;
}
