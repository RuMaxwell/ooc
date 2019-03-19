#ifndef _INTEGER_H
#define _INTEGER_H

#include "new.h"
#include "String.h"

#include <stdlib.h>

#define I(x) new(integer, x)

extern const void* integer; /* IArithmetic, IComparable */

int int_value(const void* const _self);
void set_int(void* const _self, const int value);

#endif
