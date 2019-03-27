#include "../header/IFunctor.h"

void* map(const void* const _self, void* (*f)(const void*)) {
  const Class* const* self = _self;
  if (!_self || !(*self)) error(ERR_NULLREF);
  IFunctor* i = NULL;
  if (!(i = get_interface(self, I_FUNCTOR))) error(ERR_TYPE("IFunctor"));

  return i->map(_self, f);
}
