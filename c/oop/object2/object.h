#ifndef OBJECT_H
#define OBJECT_H

typedef struct object Object;
struct object
{
    const char* name;

    void (*print)(Object* self);
};

Object* Object_new(const char* name);
void Object_delete(Object* self);
void Object_print(Object* self);

#endif /* OBJECT_H */
