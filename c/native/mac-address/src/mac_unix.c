#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

static int getMACAddressByName(char* name, unsigned char* addr, size_t len)
{
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        return 0;
    }
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, name, IFNAMSIZ - 1);
    if (ioctl(fd, SIOCGIFHWADDR, &ifr) == -1) {
        close(fd);
        return 0;
    }
    close(fd);

    memcpy(addr, ifr.ifr_hwaddr.sa_data, len);
    return 1;
}


static int getMACAddressOfFirstInterface(unsigned char* addr, size_t len)
{
    int fd;
    struct ifreq ifr[8]; /* max number of interfaces */
    struct ifconf ifc;
    int nifs;
    int i;
    int isfirst = 1;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        return 0;
    }
    ifc.ifc_len = sizeof(ifr);
    ifc.ifc_ifcu.ifcu_buf = (void*) ifr;
    if (ioctl(fd, SIOCGIFCONF, &ifc) == -1) {
        close(fd);
        return 0;
    }
    nifs = ifc.ifc_len / sizeof(struct ifreq);
    for (i = 0; i < nifs; i++) {
        if (ioctl(fd, SIOCGIFFLAGS, &ifr[i]) != -1
                && ifr[i].ifr_flags & IFF_LOOPBACK) { /* loopback */
            continue;
        }
        if (ioctl(fd, SIOCGIFHWADDR, &ifr[i]) != -1) {
            memcpy(addr, ifr[i].ifr_hwaddr.sa_data, len);
            close(fd);
            return 1;
        }
    }
    close(fd);
    return 0;
}

int main(int argc, char* argv[])
{
    char* ifname = "";
    unsigned char macAddr[6] = {0};
    int i;

    if (argc > 1) {
        ifname = argv[1];
    }

    if (!getMACAddressByName(ifname, macAddr, sizeof(macAddr))) {
        getMACAddressOfFirstInterface(macAddr, sizeof(macAddr));
    }

    printf("%.2x", macAddr[0]);
    for (i = 1; i < sizeof(macAddr); i++) {
        printf(":%.2x", macAddr[i]);
    }
    printf("\n");
    return 0;
}
