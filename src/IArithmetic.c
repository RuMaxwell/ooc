#include "../header/IArithmetic.h"

#define _CHECK_SELF(IInterface, I_MAGIC, IDescription)\
  if (!_self || !(*self)) error(ERR_NULLREF);\
  IInterface * i = NULL;\
  if (!(i = get_interface(self, I_MAGIC))) error(ERR_TYPE(IDescription));
#define _CHECK_OTHER(I_MAGIC, IDescription)\
  const Class* const* other = _other;\
  if (!_other || !(*other))\
    error(ERR_NULLREF);\
  if (!(get_interface(other, I_MAGIC)))\
    error(ERR_TYPE(IDescription));
#define _CHECK _CHECK_SELF(IArithmetic, I_ARITHMETIC, "IArithmetic") _CHECK_OTHER(I_ARITHMETIC, "IArithmetic")

void* zero(const void* _class) {
  if (!_class)
    error(ERR_NULLREF);

  const IArithmetic* i = get_interface_from_class(_class, I_ARITHMETIC);
  if (!i)
    error(ERR_TYPE("IArithmetic"));

  return i->zero();
}

void* add(void* const _self, const void* _other) {
  Class* const* self = _self;
  _CHECK
  if (*self != *other)
    error(ERR_TYPE("Two operands of `add` are required to be the same type."))
  return i->add(_self, _other);
}

void* subtract(void* const _self, const void* _other) {
  Class* const* self = _self;
  _CHECK
  if (*self != *other)
    error(ERR_TYPE("Two operands of `add` are required to be the same type."))
  return i->subtract(_self, _other);
}

void* plus(const void* const _self, const void* _other) {
  const Class* const* self = _self;
  _CHECK
  if (*self != *other)
    error(ERR_TYPE("Two operands of `add` are required to be the same type."))
  return i->plus(_self, _other);
}

void* minus(const void* const _self, const void* _other) {
  const Class* const* self = _self;
  _CHECK
  if (*self != *other)
    error(ERR_TYPE("Two operands of `subtract` are required to be the same type."))
  return i->minus(_self, _other);
}
