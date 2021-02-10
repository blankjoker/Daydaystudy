
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define UDP_BROADCAST      "255.255.255.255"
#define UDP_UNICAST        "172.20.30.2"

#define DOIP_PROTOCOL_VERSION        0x02
#define DOIP_INVERSE_VERSION         0xFD

char power_mode_true[9] =
{
    DOIP_PROTOCOL_VERSION, DOIP_INVERSE_VERSION, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x01
};
char power_mode_false[9] =
{
    DOIP_PROTOCOL_VERSION, DOIP_INVERSE_VERSION, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x02
};
char activation_line_true[9] =
{
    DOIP_PROTOCOL_VERSION, DOIP_INVERSE_VERSION, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x03
};
char activation_line_false[9] =
{
    DOIP_PROTOCOL_VERSION, DOIP_INVERSE_VERSION, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x04
};
char vehicle_announce[9] =
{
    DOIP_PROTOCOL_VERSION, DOIP_INVERSE_VERSION, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x05
};
char vehicle_announce_other_ports[9] =
{
    DOIP_PROTOCOL_VERSION, DOIP_INVERSE_VERSION, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x06
};
char routing_activation_auth_true[9] =
{
    DOIP_PROTOCOL_VERSION, DOIP_INVERSE_VERSION, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x07
};
char routing_activation_auth_false[9] =
{
    DOIP_PROTOCOL_VERSION, DOIP_INVERSE_VERSION, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x08
};
char entity_type_node[9] =
{
    DOIP_PROTOCOL_VERSION, DOIP_INVERSE_VERSION, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x09
};
char entity_type_gateway[9] =
{
    DOIP_PROTOCOL_VERSION, DOIP_INVERSE_VERSION, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x0A
};

char test_buf[8] = 
{
    0x02, 0xFD, 0x40, 0x01, 0x00,
    0x00, 0x00, 0x00
};


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
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("socket.........................\n");

    char buf[50] = { 0 };
    struct sockaddr_in srv_addr;
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_family         = AF_INET;
    srv_addr.sin_port           = htons(13400);
    srv_addr.sin_addr.s_addr    = inet_addr(UDP_UNICAST);

    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        switch(buf[0]) {
            case '1':
            {
                printf("power_mode_true change start!\n");
                if (0 > sendto(sockfd, power_mode_true, sizeof(power_mode_true), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            case '2':
            {
                printf("power_mode_false change start!\n");
                if (0 > sendto(sockfd, power_mode_false, sizeof(power_mode_false), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            case '3':
            {
                printf("activation_line_true change start!\n");
                if (0 > sendto(sockfd, activation_line_true, sizeof(activation_line_true), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            case '4':
            {
                printf("activation_line_false change start!\n");
                if (0 > sendto(sockfd, activation_line_false, sizeof(activation_line_false), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            case '5':
            {
                printf("vehicle_announce start!\n");
                if (0 > sendto(sockfd, vehicle_announce, sizeof(vehicle_announce), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            case '6':
            {
                printf("vehicle_announce_other_ports start!\n");
                if (0 > sendto(sockfd, vehicle_announce_other_ports, sizeof(vehicle_announce_other_ports), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            case '7':
            {
                printf("routing_activation_auth_true change start!\n");
                if (0 > sendto(sockfd, routing_activation_auth_true, sizeof(routing_activation_auth_true), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            case '8':
            {
                printf("routing_activation_auth_false change start!\n");
                if (0 > sendto(sockfd, routing_activation_auth_false, sizeof(routing_activation_auth_false), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            case '9':
            {
                printf("entity_type_node change start!\n");
                if (0 > sendto(sockfd, entity_type_node, sizeof(entity_type_node), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            case 'A':
            {
                printf("entity_type_gateway change start!\n");
                if (0 > sendto(sockfd, entity_type_gateway, sizeof(entity_type_gateway), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            case 'B':
            {
                printf("power_mode_true change start!\n");
                if (0 > sendto(sockfd, test_buf, sizeof(test_buf), 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr)))
                {
                    perror("sendto");
                    break;
                }
                memset(buf, 0, 100);
                break;
            }
            default:
                perror("end>>>>>>>>>>>>>>>>>>>>>>>>>!\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}
