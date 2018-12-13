#include "../header/List.h"

extern const void * list;

static void * List_constructor(void * _self, va_list * _) {
  List * self = _self;
  self->head = NULL;
  self->tail = NULL;
  return self;
}

static void * List_destructor(void * _self) {
  List * self = _self;
  self->head = NULL;
  self->tail = NULL;
  return self;
}

static void * List_clone(const void * _self) {
  const List * self = _self;
  List * p = new(list);
  p->head = self->head;
  p->tail = List_clone(self->tail);
  return p;
}

static int List_differ(const void * _self, const void * _other) {
  const List * self = _self;
  const List * other = _other;

  if (!(self->tail) && !(other->tail))
    return self->head != other->head;
  else if (!(self->tail) || !(other->tail)) {
    return 1;
  }
  else {
    return List_differ(self->tail, other->tail);
  }
}

static void * List_to_string_helper(const void * _self) {
  const List * self = _self;
}
