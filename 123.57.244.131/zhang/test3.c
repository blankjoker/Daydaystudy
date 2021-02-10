

#include <stdio.h>


union stu{

	int a;
	char b;
};


int main()
{
	union stu sss;
	sss.a = 0x12345678;
	printf("===========b = %d\n",sss.b);
	return 0;
}
