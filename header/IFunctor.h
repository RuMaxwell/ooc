#ifndef _I_FUNCTOR_H
#define _I_FUNCTOR_H

#include "new.h"

#define I_FUNCTOR 0x06150e03

typedef struct IFunctor {
  const int magic;
  void* (* map)(const void* const _self, void* (*f)(const void*));
} IFunctor;

// IFunctor f => f a -> (a -> b) -> f b
void* map(const void* const _self, void* (*f)(const void*));

#endif
