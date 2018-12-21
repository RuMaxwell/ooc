#ifndef _OBJ_STRING_H
#define _OBJ_STRING_H

#include "./new.h"
#include "./interfaces.h"
#include <string.h>

#define S(chs) new(string, chs)

extern const void * string; /* ISequential */

char * c_str(const void * const _self) _CONST_METHOD;

/*
 * Make several object a string. Objects are not separated by any characters.
 */
void * compose(int count, ...);

#endif
