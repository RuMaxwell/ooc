#include "../header/IApplicative.h"

void* apply(const void* const _self, const void* _other) {
  const Class* const* self = _self;
  if (!_self || !(*self)) error(ERR_NULLREF);
  IApplicative* i = NULL;
  if (!(i = get_interface(self, I_APPLICATIVE))) error(ERR_TYPE("IApplicative"));
  const Class* const* other = _other;
  if (!_other || !(*other))
    error(ERR_NULLREF);
  if (!(get_interface(other, I_APPLICATIVE)))
    error(ERR_TYPE("IApplicative"));
  if (*self != *other)
    error("TypeError: Two operands are required to be the same container type.");

  return i->apply(_self, _other);
}
