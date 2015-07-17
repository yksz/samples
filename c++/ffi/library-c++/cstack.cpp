#include "cstack.h"
#include <stack>
#include <cstddef> // size_t

struct cstack {
    std::stack<void*> stack;
};

cstack_t* cstack_new(void) {
    return new cstack;
}

void cstack_delete(cstack_t* self) {
    delete self;
}

size_t cstack_size(cstack_t* self) {
    return self->stack.size();
}

int cstack_empty(cstack_t* self) {
    return self->stack.empty() ? 1 : 0;
}

void cstack_pop(cstack_t* self) {
    self->stack.pop();
}

void cstack_push(cstack_t* self, const void* element) {
    self->stack.push(const_cast<void*>(element));
}

void* cstack_top(cstack_t* self) {
    return self->stack.top();
}
