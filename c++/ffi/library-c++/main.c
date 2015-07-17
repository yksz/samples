#include <stdio.h>
#include "cstack.h"

int main() {
    cstack_t* stack = cstack_new();
    cstack_push(stack, "first");
    cstack_push(stack, "second");
    cstack_push(stack, "third");
    while (!cstack_empty(stack)) {
        printf("element: %s\n", (char*) cstack_top(stack));
        cstack_pop(stack);
    }
    cstack_delete(stack);
    return 0;
}
