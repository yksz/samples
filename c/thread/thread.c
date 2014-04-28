#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static void* start_routine(void* args)
{
    for (int i = 1; i <= 5; i++) {
        printf("count: %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, start_routine, (void *) NULL);
    pthread_join(thread, NULL);
    return 0;
}
