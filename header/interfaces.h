#ifndef _INTERFACES_H
#define _INTERFACES_H

#include "./new.h"

#define I_CONTAINER 0
#define I_CONTAINER_METHOD

typedef struct IContainer {
  const int magic;
  void * (* concat)(void * _a, void * _b);
} IContainer;

I_CONTAINER_METHOD void * concat(void * _a, void * _b);

#endif
