#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")

static int getMACAddressByName(char* name, unsigned char* addr, size_t len)
{
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

    pAdapterInfo = (IP_ADAPTER_INFO*) malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        return 0;
    }
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*) malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            fprintf(stderr, "ERROR: out of memory\n");
            return 0;
        }
    }
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR) {
        for (pAdapter = pAdapterInfo; pAdapter != NULL; pAdapter = pAdapter->Next) {
            if (strcmp(pAdapter->AdapterName, name) == 0) {
                memcpy(addr, pAdapter->Address, len);
                free(pAdapterInfo);
                return 1;
            }
        }
    }
    free(pAdapterInfo);
    return 0;
}

static int getMACAddressOfFirstInterface(unsigned char* addr, size_t len)
{
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

    pAdapterInfo = (IP_ADAPTER_INFO*) malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        return 0;
    }
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*) malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            fprintf(stderr, "ERROR: out of memory\n");
            return 0;
        }
    }
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR) {
        for (pAdapter = pAdapterInfo; pAdapter != NULL; pAdapter = pAdapter->Next) {
            if (pAdapter->Type != MIB_IF_TYPE_LOOPBACK) { /* not loopback */
                memcpy(addr, pAdapter->Address, len);
                free(pAdapterInfo);
                return 1;
            }
        }
    }
    free(pAdapterInfo);
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
