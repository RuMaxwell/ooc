#ifndef _OBJ_STRING_H
#define _OBJ_STRING_H

#include "./new.h"
#include "./interfaces.h"
#include <string.h>

extern const void * string;

typedef struct String /* ISequential */ {
  const void * class;
  size_t length;
  char * chs;
} String;

char * c_str(const void * _self) _CONST_METHOD;

#endif
