#include "../header/Object.h"

void * Object_constructor(void * _self, va_list * _) {
  return _self;
}

void * Object_destructor(void * _self) {
  return _self;
}

void * Object_clone(const void * _self) {
  return new(object);
}

int Object_differ(const void * _self, const void * _other) {
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
