#ifndef _OBJ_STRING_H
#define _OBJ_STRING_H

#include "./new.h"
#include <string.h>

extern const void * string;

typedef struct String {
  const void * class;
  char * chs;
} String;

#endif
