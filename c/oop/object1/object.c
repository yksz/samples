#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "object.h"

static void Object_privateMethod(Object* self);

Object* Object_new(char* name)
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

void Object_delete(Object* self)
{
    free(self);
}

void Object_print(Object* self)
{
    printf("Object.name: %s\n", self->name);
    Object_privateMethod(self);
}

static void Object_privateMethod(Object* self)
{
    printf("Object_privateMethod()\n");
}
