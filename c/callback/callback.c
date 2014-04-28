#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void init()
{
    srand((unsigned) time(NULL));
}

static int get_rand(int min, int max)
{
    return min + (int) (rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

static void add(int* num, void (*succeeded)(int* val), void (*failed)())
{
    if (get_rand(0, 1)) {
        *num += 1;
        succeeded(num);
    } else {
        failed();
    }
}

static void succeeded(int* val)
{
    printf("added, and val = %d\n", *val);
}

static void failed()
{
    printf("\n");
}

int main()
{
    init();
    int num = 0;
    for (int i = 0; i < 9; i++) {
        printf("%d loop: ", i+1);
        add(&num, succeeded, failed);
    }
    return 0;
}
