#include "../header/Object.h"

typedef struct Object {
  const void * class;
} Object;


void * Object_constructor(void * const _self, va_list * _) {
  return _self;
}

void * Object_destructor(void * const _self) {
  return _self;
}

void * Object_clone(const void * const _self) {
  return new(object);
}

int Object_differ(const void * const _self, const void * _other) {
  return _self != _other;
}

static const Class _object = {
  /* size */ sizeof (Object),
  /* description */ "object",
  /* interfaces */ NULL,
  /* constructor */ Object_constructor,
  /* destructor */ Object_destructor,
  /* clone */ Object_clone,
  /* differ */ Object_differ,
  /* to_string */ NULL
};

const void * object = & _object;
