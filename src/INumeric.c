#include "../header/INumeric.h"

void* identity(const void* _Class) {
  if (!_Class)
    error(ERR_NULLREF);

  const INumeric* i = get_interface_from_class(_Class, I_NUMERIC);
  if (!i)
    error(ERR_TYPE("INumeric"));

  return i->identity();
}

void* multiply(void* const _INumeric, const void* _other) {
  const Class* const* self = _INumeric;
  if (!_INumeric || !(*self)) error(ERR_NULLREF);
  INumeric* i = NULL;
  if (!(i = get_interface(self, I_NUMERIC))) error(ERR_TYPE("INumeric"));
  const Class* const* other = _other;
  if (!_other || !(*other)) error(ERR_NULLREF);
  if (!(get_interface(other, I_NUMERIC))) error(ERR_TYPE("INumeric"));

  if (*self != *other)
    error(ERR_TYPE("the same type"));

  return i->multiply(_INumeric, _other);
}

void* times(const void* const _INumeric, const void* _other) {
  const Class* const* self = _INumeric;
  if (!_INumeric || !(*self)) error(ERR_NULLREF);
  INumeric* i = NULL;
  if (!(i = get_interface(self, I_NUMERIC))) error(ERR_TYPE("INumeric"));
  const Class* const* other = _other;
  if (!_other || !(*other)) error(ERR_NULLREF);
  if (!(get_interface(other, I_NUMERIC))) error(ERR_TYPE("INumeric"));

  if (*self != *other)
    error(ERR_TYPE("the same type"));

  return i->times(_INumeric, _other);
}
