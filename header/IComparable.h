#ifndef _I_COMPARABLE_H
#define _I_COMPARABLE_H

#include "./new.h"

#define I_COMPARABLE 0x030f0d10 // parseInt("COMP".map(x => parseInt(x - 'A')).join())

typedef struct IComparable {
  const int magic;
  int (* compare)(const void * const _self, const void * _other);
} IComparable;

int compare(const void * const _self, const void * _other);

#endif
