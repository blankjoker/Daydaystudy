

#include <stdio.h>

#define aa ('1', '2')

int main(int argc, char const *argv[])
{
	/* code */
	// char buf[3] = {aa, 's'};
	// int i = 0;
	// printf(">>>>>>>>>>>>>%s\n", buf);
	// printf("recv is :\n");
	// for(i = 0; i <=	 2; i++) {

	// 	printf("%c", buf[i]);
	// }
	// printf("\n");
	// char buf[2] = {0x11, 0x12};
	// printf(">>>>>>>>>>>>%02X\n", buf[0]); 
	// printf(">>>>>>>>>>>>%02X\n", buf[1]); 
	// printf(">>>>>>>>>>>>%s\n", buf); 
	char buf1 = 0x04;
	char buf[5] =
	{
		0x01, 0x04, buf1, buf1, buf1
	};
	printf("%x\n", buf[0]);
	printf("%x\n", buf[1]);
	printf("%x\n", buf[2]);
	printf("%x\n", buf[3]);
	printf("%x\n", buf[4]);
	return 0;
}