#ifndef _LIST_H
#define _LIST_H

#include "./new.h"

extern const void * list;

typedef struct List {
  const void * class;
  void * head;
  struct List * tail;
} List;

#endif
