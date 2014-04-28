#ifndef OBJECT_H
#define OBJECT_H

typedef struct object Object;
struct object
{
    char* name;
};

Object* Object_new(char* name);
void Object_delete(Object* self);
void Object_print(Object* self);

#endif /* OBJECT_H */
