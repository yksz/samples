#include "object.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static Object* instance = NULL;

static Object* Object_new(const char* name)
{
    assert(name != NULL);

    Object* obj = (Object*) calloc(1, sizeof(Object));
    if (obj == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        exit(EXIT_FAILURE);
    }
    obj->name = name;
    return obj;
}

static Object* getInstance() {
    if (instance == NULL) {
        instance = Object_new("heap");
    }
    return instance;
}

void Heap_print()
{
    Object* obj = getInstance();
    printf("Object.name: %s\n", obj->name);
}
