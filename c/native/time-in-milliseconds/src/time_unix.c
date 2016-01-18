#include <stdio.h>
#include <time.h>
#include <sys/time.h>

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
