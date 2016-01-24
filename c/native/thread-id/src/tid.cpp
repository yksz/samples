#include <stdio.h>
#include <thread>
#include <vector>
#if defined(_WIN32) || defined(_WIN64)
 #include <windows.h>
#else
 #if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
  #include <sys/syscall.h>
  #include <unistd.h>
 #else
  #include <pthread.h>
 #endif /* defined(__linux__) || (defined(__APPLE__) && defined(__MACH__)) */
#endif /* defined(_WIN32) || defined(_WIN64) */

static long getCurrentThreadID()
{
#if __linux__
    return syscall(SYS_gettid);
#elif defined(__APPLE__) && defined(__MACH__)
    return syscall(SYS_thread_selfid);
#elif defined(_WIN32) || defined(_WIN64)
    return GetCurrentThreadId();
#else
    return (long) pthread_self();
#endif /* __linux__ */
}

int main(void)
{
    int nThreads = 10;
    std::vector<std::thread> threads;
    for (int i = 1; i <= nThreads; i++) {
        threads.push_back(std::thread([=]() {
            printf("Thread th%02d: ThreadID=%ld\n", i, getCurrentThreadID());
            printf("Thread th%02d: ThreadID=%ld\n", i, getCurrentThreadID());
        }));
    }
    for (std::thread& th : threads) {
        th.join();
    }

    printf("Thread main: ThreadID=%ld\n", getCurrentThreadID());
    printf("Thread main: ThreadID=%ld\n", getCurrentThreadID());
    return 0;
}
