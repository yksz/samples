#include <iostream>
#include "cstack.h"

int main() {
    cstack_t* stack = cstack_new();
    cstack_push(stack, "first");
    cstack_push(stack, "second");
    cstack_push(stack, "third");
    while (!cstack_empty(stack)) {
        const char* element = (const char*) cstack_top(stack);
        std::cout << "element: " << element << std::endl;
        cstack_pop(stack);
    }
    cstack_delete(stack);
    return 0;
}
