
#ifndef ME_SOCKET__
#define ME_SOCKET__

#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

class Me_Socket
{
private:
    /* data */
    static Me_Socket *m_instance;
public:
    Me_Socket();
    virtual ~Me_Socket();

    Me_Socket(const Me_Socket& other);
    Me_Socket& operator=(const Me_Socket& other);

    int me_os_socket(int domain, int type, int protocol);
    int me_os_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    int me_os_connect(int sockfd, struct sockaddr *addr, socklen_t addrlen);
    void me_os_get_ifname(char* ifname, int fd, char *ip);
    int me_os_get_ip(const char *ifname, char *ip, int iplen);

    static Me_Socket* insrance();
};

#endif // ME_SOCKET__
/* EOF */