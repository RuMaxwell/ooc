#include "../header/ImmutableList.h"

extern const void * ulist;

typedef struct UList {
  const void * class;
  void * head;
  struct UList * tail;
} UList;


static void * UList_constructor(void * const _self, va_list * _) {
  UList * self = _self;
  self->head = NULL;
  self->tail = NULL;
  return self;
}

static void * UList_destructor(void * const _self) {
  UList * self = _self;
  self->head = NULL;
  self->tail = NULL;
  return self;
}

static void * UList_clone(const void * const _self) {
  const UList * self = _self;

  if (!_self)
    return NULL;

  UList * p = new(ulist);
  p->head = self->head;
  p->tail = UList_clone(self->tail);
  return p;
}

static int UList_differ(const void * const _self, const void * _other) {
  const UList * self = _self;
  const UList * other = _other;

  if (!(self->tail) && !(other->tail))
    return self->head != other->head;
  else if (!(self->tail) || !(other->tail)) {
    return 1;
  }
  else {
    return UList_differ(self->tail, other->tail);
  }
}

static void * UList_to_string_helper(const void * const _self) {
  const UList * self = _self;
  void * res = S("");
  if (self) {
    const void * head = self->head;
    const void * tail = self->tail;
    if (head) {
      void * comma = S(",");
      void * str, * res1, * res2, * res3;
      str = to_string(head);
      res1 = concat(res, str);
      if (((UList *)tail)->head)
        res2 = concat(res1, comma);
      else
        res2 = res1;
      res3 = concat(res2, UList_to_string_helper(tail));
      delete(res); delete(str); delete(res1); delete(res2);
      return res3;
    }
    return res;
  }
  return res;
}

static void * UList_to_string(const void * const _self) {
  void * res = UList_to_string_helper(_self);
  void * lbr = S("[");
  void * rbr = S("]");
  void * res1 = concat(lbr, res);
  void * res2 = concat(res1, rbr);
  delete(res); delete(lbr); delete(rbr); delete(res1);
  return res2;
}

static const Class _ulist = {
  .size = sizeof (UList),
  .description = "ulist",
  .interfaces = NULL,
  .constructor = UList_constructor,
  .destructor = UList_destructor,
  .clone = UList_clone,
  .differ = UList_differ,
  .to_string = UList_to_string
};

const void * ulist = & _ulist;

void * cons(void * head, const void * const _self) {
  const UList * self = _self;

  if (!_self || !(self->class))
    error(ERR_NULLREF);

  if (!is_instance(self, ulist))
    error(ERR_TYPE("ulist"));

  UList * p = new(ulist);
  p->head = head;
  p->tail = (void *)self;
  return p;
}
