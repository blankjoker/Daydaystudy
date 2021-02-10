#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	
	static long buf[10] = {0};
	memset(buf, 0, 10);
	++buf[0];
	printf(">>>>>>:%ld\n", buf[0]);

	return 0;
}