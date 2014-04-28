#include <stdio.h>
#include "object.h"

static void stack_object()
{
    printf("[stack_object] begin\n");

    Object obj1 = { .name = "obj1" };
    Object obj2 = { .name = "obj2" };

    Object_print(&obj1);
    Object_print(&obj2);

    printf("[stack_object] end\n\n");
}

static void heap_object()
{
    printf("[heap_object] begin\n");

    Object* obj1 = Object_new("obj1");
    Object* obj2 = Object_new("obj2");

    obj1->print(obj1);
    obj2->print(obj2);

    Object_delete(obj1);
    obj1 = NULL;
    Object_delete(obj2);
    obj2 = NULL;

    printf("[heap_object] end\n\n");
}

int main()
{
    stack_object();
    heap_object();
    return 0;
}
