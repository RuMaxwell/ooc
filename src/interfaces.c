#include "../header/interfaces.h"

I_SEQUENTIAL_METHOD size_t length(void * _self) {
  const Class * const * self = _self;

  if (!_self || !(*self))
    error(ERR_NULLREF);
  ISequential * i = NULL;
  if (!(i = get_interface(self, I_SEQUENTIAL)))
    error(ERR_TYPE("ISequential"));

  return i->length(_self);
}

I_SEQUENTIAL_METHOD void * concat(void * _self, void * _other) {
  const Class * const * self = _self;
  const Class * const * other = _other;

  if (!_self || !_other || !(*self) || !(*other))
    error(ERR_NULLREF);
  ISequential * i = NULL;
  if (!(i = get_interface(self, I_SEQUENTIAL)))
    error(ERR_TYPE("ISequential"));

  return i->concat(_self, _other);
}
