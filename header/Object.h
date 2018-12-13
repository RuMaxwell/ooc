#ifndef _OBJECT_H
#define _OBJECT_H

#include "./new.h"

extern const void * object;

typedef struct Object {
  const void * class;
} Object;

#endif // !_OBJECT_H
