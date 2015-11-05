#ifndef OBJECT_H
#define OBJECT_H

typedef struct interface Interface;
struct interface
{
    void (*destroy)(void* self);
    void (*print)(void* self);
};

typedef struct object Object;
struct object
{
    Interface interface;
    const char* name;
};

Object* Object_new(const char* name);
void Object_print(Object* self);

#endif /* OBJECT_H */
