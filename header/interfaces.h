#ifndef _INTERFACES_H
#define _INTERFACES_H

#include "./new.h"

#define I_SEQUENTIAL 0
#define I_SEQUENTIAL_METHOD

typedef struct ISequential {
  const int magic;
  size_t (*length)(void * _self);
  void * (* concat)(void * _self, void * _other);
} ISequential;

I_SEQUENTIAL_METHOD size_t length(void * _self);
I_SEQUENTIAL_METHOD void * concat(void * _self, void * _other);

#endif
