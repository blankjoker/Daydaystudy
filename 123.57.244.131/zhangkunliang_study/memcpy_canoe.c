


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


uint8_t protocol_persion_test = 0x03;

unsigned char buf2[10] =
{
	0x01, 0x02, 0x03, 0x04, 0x05,
	0x01, 0x02, 0x03, 0x06, 0x05
};


void canoe_strcat(uint8_t protocol_persion, uint8_t inverse_protocol_persion)
{
	uint8_t one = 0;
	uint8_t two = 1;
	buf2[one] = protocol_persion;
	printf("%02x\n", buf2[0]);
	buf2[two] = inverse_protocol_persion;
	printf("%02x\n", buf2[1]);

}


int main(int argc, char const *argv[])
{
	/* code */

	// char buf2[10] =
	// {
	// 	protocol_persion_test, 0x02, 0x03, 0x04, 0x05,
	// 	0x01, 0x02, 0x03, 0x06, 0x05
	// };


	canoe_strcat(0x03, 0xfa);
	uint8_t i = 0;
	for(i = 0; i<10; i++) {

		printf("%02X", buf2[i]);
	}
	printf("\n");

	printf("%02X\n", 0xfd);

	return 0;
}