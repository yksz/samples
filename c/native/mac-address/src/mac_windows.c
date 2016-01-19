#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")

static void getMACAddress(unsigned char* addr, size_t len)
{
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    size_t i;

    pAdapterInfo = (IP_ADAPTER_INFO*) malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        return;
    }
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*) malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            fprintf(stderr, "ERROR: out of memory\n");
            return;
        }
    }
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        if (pAdapter) {
            for (i = 0; i < len; i++) {
                addr[i] = pAdapter->Address[i];
            }
        }
    }
    free(pAdapterInfo);
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
