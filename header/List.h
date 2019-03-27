/*
 * Doubly linked list
 */

#ifndef _LIST_H
#define _LIST_H

#include "./new.h"
#include "./interfaces.h"
#include "./String.h"

extern const void * list; /* IFunctor, IApplicative, ISequential */

void * LIST(int count, ...);

#endif
