#ifndef _OBJ_STRING_H
#define _OBJ_STRING_H

#include "./new.h"
#include "./interfaces.h"
#include <string.h>

extern const void * string; /* ISequential */

char * c_str(const void * const _self) _CONST_METHOD;

#endif
