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

// Do the same method with every matrix element.
// R = map f A
// newElement f(scalar, matrixElement)
void* scalarMultiply(const void* const _self, const void* scalar, void* (*f)(void*, void*));
// Do the same method with every corresponding elements of two matrices.
// R = map f A B
// newElement f(selfElement, otherElement)
void* scalarMMultiply(const void* const _self, const void* _other, void* (*f)(void*, void*));
// Matrices multiplication.
// R = A x B
void* mMultiply(const void* const _self, const void* _other);
// Calc inversed matrix. R = A^(-1)
// Warns when the matrix is very possibly singular.
void* mInverse(const void* const _self);
// Calc transposed matrix. R = A^T
void* mTranspose(const void* const _self);

#endif
