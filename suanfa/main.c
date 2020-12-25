
#include <stdio.h>
#include "hextobin.h"
const char *TipString[] = 
{
	"bin file to hex file success!",
	"line data of hex file is too large",
	"line data of hex file is too short",
	"line data of hex file is no colon",
	"line data of hex file type is error",
	"line data of hex file length is error",
	"line data of hex file check error",
	"hex file is not exist",
	"bin file path is error",
	"hex file is no end"
};
int main(int argc, char *argv[])
{
	RESULT_STATUS res;
	if (argc != 3)
	{
		printf("para doesn't match!\r\n");
	}
	res = HexFile2BinFile(argv[1], argv[2]);
	printf("%s\r\n", TipString[res]);
	if (res != RES_OK)
	{
		return -1;
	}
	return 0;
}
