
#include <stdio.h>

int func(int x)
{
	int count = 0;
	while(x > 0)
	{
		x = (x >> 1);
		count++;
	}
	return count;
}

int main()
{

	int num = func(9999);
	printf("=============num = %d\n", num);
	return 0;

}
