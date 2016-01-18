#include <stdio.h>
#if (defined(_WIN32) || defined(_WIN64)) || defined(__CYGWIN__)
#include <windows.h>
#else
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#endif

static long getCurrentThreadID()
{
#if defined(__linux)
    return syscall(SYS_gettid);
#elif defined(__APPLE__) && defined(__MACH__)
    return syscall(SYS_thread_selfid);
#elif (defined(_WIN32) || defined(_WIN64)) || defined(__CYGWIN__)
    return GetCurrentThreadId();
#else
    return -1;
#endif
}

int main(void)
{
    printf("ThreadID=%ld\n", getCurrentThreadID());
    return 0;
}
