#ifndef _MATRIX_H
#define _MATRIX_H

#include "new.h"
#include "IArithmetic.h"
#include "List.h"
#include "String.h"

extern const void* matrix; /* IArithmetic, IContainer */

size_t rows(const void* const _self);
size_t cols(const void* const _self);
void* getMData(const void* const _self, size_t r, size_t c);
void setMData(void* const _self, size_t r, size_t c, void* value);
void fill(void* const _self, void* value);

// Calc inversed matrix. R = A^(-1)
// Warns when the matrix is very possibly singular.
void* mInverse(const void* const _matrix);
// Calc transposed matrix. R = A^T
void* mTranspose(const void* const _matrix);

// `(IArithmetic a, INumeric a) => Matrix a -> Matrix a -> Matrix a`.
// Matrices multiplication.
// R = A x B.
// Required `_self` and `_other` to be 2 matrices of elements of `INumeric`.
void* mMultiply(_IArithmetic_ _INumeric_ const void* const _self, _IArithmetic_ _INumeric_ const void* _other);

#endif
