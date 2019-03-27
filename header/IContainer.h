#ifndef _I_CONTAINER_H
#define _I_CONTAINER_H

#include "new.h"

#define I_CONTAINER 0x030f0e14

typedef struct IContainer {
  const int magic;
  const void* (*getElementType)(const void* const _self);
  size_t (*count)(const void* const _self);
  int (*contains)(const void* const _self, const void* obj);
  int (*some)(const void* const _self, int (*filter)(const void* obj));
  int (*every)(const void* const _self, int (*filter)(const void* obj));
} IContainer;

// Get the type of elements of the container.
// Returns type `any` in following conditions:
//  1. The container is null;
//  2. The container contains null element(s);
//  3. The container contains more than one type of objects.
// In other cases, the method returns the type of all the elements in the container.
const void* getElementType(const void* const _IContainer);

// Returns the count of elements in the container.
size_t count(const void* const _IContainer);

// Check whether the container is empty.
_NO_NEED_IMPLEMENT int is_empty(const void* const _IContainer); // **** This method is implemented by `count`.

// Check whether the container contains certain object.
// Will ALWAYS return false if the object is `NULL`.
int contains(const void* const _IContainer, const void* obj);

// Check whether the container has an objects satisfying a certain condition
// (given by the `filter` function).
int some(const void* const _IContainer, int (*filter)(const void* element));

// Check whether all the elements in the container satisfies a certain condition
// (given by the `filter` function).
int every(const void* const _IContainer, int (*filter)(const void* element));

#endif
