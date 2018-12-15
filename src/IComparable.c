#include "../header/IComparable.h"

#define _CHECK\
  const Class * const * self = _self;\
  if (!_self || !(*self)) error(ERR_NULLREF);\
  IComparable * i = NULL;\
  if (!(i = get_interface(self, I_COMPARABLE))) error(ERR_TYPE("IComparable"));

int compare(const void * const _self, const void * _other) {
  _CHECK
  const Class * const * other = _other;
  if (!_other || !(*other))
    error(ERR_NULLREF);
  if (!(get_interface(other, I_COMPARABLE)))
    error(ERR_TYPE("IComparable"));

  return i->compare(_self, _other);
}
