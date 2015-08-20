#include "object.h"
#include <stdio.h>
#include <stdlib.h>

static Object instance = { .name = "static" };

void Static_print()
{
    printf("Object.name: %s\n", instance.name);
}
