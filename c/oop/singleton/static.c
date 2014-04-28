#include <stdio.h>
#include <stdlib.h>
#include "object.h"

static Object instance = { .name = "static" };

void Static_print()
{
    printf("Object.name: %s\n", instance.name);
}
