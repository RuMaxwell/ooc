#include "../header/ISequential.h"

#define _CHECK_INTERFACE(IInterface, I_MAGIC, IDescription)\
  const Class * const * self = _self;\
  if (!_self || !(*self)) error(ERR_NULLREF);\
  IInterface * i = NULL;\
  if (!(i = get_interface(self, I_MAGIC))) error(ERR_TYPE(IDescription));
#define _CHECK _CHECK_INTERFACE(ISequential, I_SEQUENTIAL, "ISequential")

size_t length(const void * const _self) {
  _CHECK
  return i->length(_self);
}

void * head(const void * const _self) {
  _CHECK
  if (length(_self) <= 0)
    error(ERR_NO_HEAD);

  return i->head(_self);
}

void * tail(const void * const _self) {
  _CHECK
  return i->tail(_self);
}

void * get(const void * const _self, size_t index) {
  _CHECK
  if (index < 0 || index >= length(_self))
    error(ERR_INDEX);

  return i->get(_self, index);
}

void set(void * const _self, size_t index, void * _object) {
  _CHECK
  if (index < 0 || index >= length(_self))
    error(ERR_INDEX);

  i->set(_self, index, _object);
}

size_t insert(void * const _self, size_t index, const void * _object) {
  _CHECK
  if (index < 0 || index > length(_self))
    error(ERR_INDEX);

  return i->insert(_self, index, _object);
}

void * drop(void * const _self, size_t index) {
  _CHECK
  if (index < 0 || index >= length(_self))
    error(ERR_INDEX);

  return i->drop(_self, index);
}

void * append(void * const _self, const void * _other) {
  const Class * const * other = _other;
  if (!_other || !(*other))
    error(ERR_NULLREF);
  if (!(get_interface(other, I_SEQUENTIAL)))
    error(ERR_TYPE("ISequential"));

  _CHECK
  return i->append(_self, _other);
}

size_t push(void * const _self, const void * _object) {
  return insert(_self, length(_self), _object);
}

void * pop(void * const _self) {
  return drop(_self, length(_self) - 1);
}

void * concat(const void * const _self, const void * _other) {
  void * res = clone(_self);
  append(res, _other);
  return res;
}
