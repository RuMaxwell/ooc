#ifndef _MATRIX_H
#define _MATRIX_H

#include "new.h"
#include "IArithmetic.h"
#include "List.h"
#include "String.h"

extern const void* matrix; /* IArithmetic */

size_t rows(const void* const _self);
size_t cols(const void* const _self);
void* getMData(const void* const _self, size_t r, size_t c);
void setMData(void* const _self, size_t r, size_t c, void* value);
void fill(void* const _self, void* value);

#endif
