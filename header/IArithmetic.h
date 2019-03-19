#ifndef _I_ARITHMETIC_H
#define _I_ARITHMETIC_H

#include "new.h"

#define I_ARITHMETIC 0x01120914

typedef struct IArithmetic {
  const int magic;
  void* (*add)(void* const _self, const void* _other);
  void* (*subtract)(void* const _self, const void* _other);
  void* (*plus)(const void* const _self, const void* _other);
  void* (*minus)(const void* const _self, const void* _other);
} IArithmetic;

void* add(void* const _self, const void* _other);
void* subtract(void* const _self, const void* _other);
void* plus(const void* const _self, const void* _other);
void* minus(const void* const _self, const void* _other);

#endif
