
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define UDP_BROADCAST 	   "255.255.255.255"
#define UDP_UNICAST        "192.168.29.36"

void ne_doip_convert_mac(char *str_out, const char *str_in)
{
    if (NULL == str_out || NULL == str_in) {
        return;
    }
    uint32_t n;
    uint8_t m = 0;
    // Every two characters are stored as a numeric value
    for (n = 0; n < strlen(str_in); n += 2) {
        uint8_t sum;
        // n  0 2 4 6....
        if ((str_in[n] >= 'A') && (str_in[n] <= 'F')) {
            sum = (str_in[n] - 'A' + 10) * 16;
        }
        else {
            sum = (str_in[n] - '0') * 16;
        }
        // n+1   1 3 5 7....
        if (str_in[n + 1] >= 'A' && str_in[n + 1] <= 'F') {
            sum += str_in[n + 1] - 'A' + 10;
        }
        else {
            sum += str_in[n + 1] - '0';
        }

        str_out[m] = sum;
        m++;
    }
}

int main()
{

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	printf("socket...........\n");


	char buf[100] = { 0 };
	struct sockaddr_in srv_addr;
	memset(&srv_addr, 0, sizeof(srv_addr));
	srv_addr.sin_family 		= AF_INET;
	srv_addr.sin_port 			= htons(13400);
	srv_addr.sin_addr.s_addr 	= inet_addr(UDP_UNICAST);
	

	while (1)
	{
		fgets(buf, sizeof(buf), stdin);
		ne_doip_convert_mac(buf, buf);
		if (0 > sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
		{
			perror("sendto");
			break;
		}
		memset(buf, 0, 100);
	}


	close(sockfd);

	return 0;
}
