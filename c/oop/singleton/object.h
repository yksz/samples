#ifndef OBJECT_H
#define OBJECT_H

typedef struct object Object;
struct object
{
    char* name;
};

void Static_print();
void Heap_print();

#endif /* OBJECT_H */
