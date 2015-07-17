#ifndef CSTACK_H
#define CSTACK_H

#include <stddef.h> // size_t

#ifdef __cplusplus
extern "C" {
# endif // __cplusplus

typedef struct cstack cstack_t;

cstack_t* cstack_new    (void);
void      cstack_delete (cstack_t* self);
size_t    cstack_size   (cstack_t* self);
int       cstack_empty  (cstack_t* self);
void      cstack_pop    (cstack_t* self);
void      cstack_push   (cstack_t* self, const void* element);
void*     cstack_top    (cstack_t* self);

#ifdef __cplusplus
} // extern "C"
# endif // __cplusplus

#endif // CSTACK_H
