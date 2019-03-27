#ifndef _I_NUMERIC_H
#define _I_NUMERIC_H

#include "new.h"

#define I_NUMERIC 0x0e150d05

typedef struct INumeric {
  const int magic;
  void* (*identity)();
  void* (*multiply)(void* const _self, const void* _other);
  void* (*times)(const void* const _self, const void* _other);
} INumeric;

// Gets an "identity" value of the numeric type. Multiplying any value with identity will just return the value itself.
void* identity(const void* _Class);

// Multiplies an `INumeric` with another value in the SAME TYPE and stores the result in the original one.
// Shall return itself for chain calls.
void* multiply(void* const _INumeric, const void* _other);

// Multiplies an `INumeric` with another value in the SAME TYPE and returns it.
void* times(const void* const _INumeric, const void* _other);

#endif
