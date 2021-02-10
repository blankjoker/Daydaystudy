
#include <stdio.h>

char * getchar_buf(void)
{
	char buf[10] = { 0 };
	int i = 0;
	for (i = 0; i < 10; i++) {
		/* code */
		buf[i] = i;
	}
	return buf;
} 

int main(int argc, char const *argv[])
{

	char *buf = getchar_buf();
	int i = 0;
	for (i = 0; i < 10; i++) {
		/* code */
		printf("%d\n", buf[i]);
	}
	return 0;
}