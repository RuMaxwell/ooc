#ifndef _IMMUTABLE_LIST_H
#define _IMMUTABLE_LIST_H

#include "./new.h"
#include "./String.h"

extern const void * ulist;

void * cons(void * head, const void * const _self) _CONST_METHOD;

#endif
