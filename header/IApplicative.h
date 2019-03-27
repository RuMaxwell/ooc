#ifndef _I_APPLICATIVE_H
#define _I_APPLICATIVE_H

#include "new.h"

#define I_APPLICATIVE 0x0110100b

typedef struct IApplicative {
  const int magic;
  void* (*apply)(const void* const _self, const void* _other);
} IApplicative;

// IApplicative f => f a -> f (a -> b) -> f b
void* apply(const void* const _self, const void* _other);

#endif
