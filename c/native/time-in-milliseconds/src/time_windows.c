#include <stdio.h>
#include <time.h>
#include <winsock2.h>

static int gettimeofday(struct timeval* tv, void* tz)
{
    const UINT64 epochFileTime = 116444736000000000ULL;
    FILETIME ft;
    ULARGE_INTEGER li;
    UINT64 t;

    if (tv == NULL) {
        return -1;
    }
    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    t = (li.QuadPart - epochFileTime) / 10;
    tv->tv_sec = t / 1000000;
    tv->tv_usec = t % 1000000;
    return 0;
}

int main(void)
{
    struct timeval tv;
    time_t now;
    char timestr[32];

    gettimeofday(&tv, NULL);
    now = tv.tv_sec;
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localtime(&now));
    sprintf(timestr, "%s.%06ld", timestr, tv.tv_usec);
    printf("%s\n", timestr);
    return 0;
}
