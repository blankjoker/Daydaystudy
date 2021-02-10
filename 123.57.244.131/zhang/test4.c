

#include <stdio.h>

int two(int x)
{
	if (x == 0) {
		return 0;
	}
	else {

		two(x/2);
		printf("%d", x%2);
		return;
	}
}



int main()
{
	two(128);
	printf("\n");

	return 0;

}
