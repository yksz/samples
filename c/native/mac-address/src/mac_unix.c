#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

static void getMACAddress(unsigned char* addr, size_t len)
{
    int fd;
    struct ifreq ifreq;
    int i;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifreq.ifr_addr.sa_family = AF_INET;
    strncpy(ifreq.ifr_name, "eth0", IFNAMSIZ - 1);
    ioctl(fd, SIOCGIFHWADDR, &ifreq);
    close(fd);

    for (i = 0; i < len; i++) {
        addr[i] = (unsigned char) ifreq.ifr_hwaddr.sa_data[i];
    }
}

int main(void)
{
    unsigned char macAddr[6];
    int i = 0;

    getMACAddress(macAddr, sizeof(macAddr));

    printf("%.2x", macAddr[i]);
    for (i = 1; i < sizeof(macAddr); i++) {
        printf(":%.2x", macAddr[i]);
    }
    printf("\n");
    return 0;
}
