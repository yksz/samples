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

    Interface* inf1 = (Interface*) Object_new("obj1");
    Object* obj2 = Object_new("obj2");

    inf1->print(inf1);
    obj2->interface.print(obj2);

    inf1->destroy(inf1);
    inf1 = NULL;
    obj2->interface.destroy(obj2);
    obj2 = NULL;

    printf("[heap_object] end\n\n");
}

int main()
{
    stack_object();
    heap_object();
    return 0;
}
