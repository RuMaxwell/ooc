#include "../header/IContainer.h"

const void* getElementType(const void* const _IContainer) {
  const Class* const* self = _IContainer;
  if (!_IContainer || !(*self)) error(ERR_NULLREF);
  IContainer* i = NULL;
  if (!(i = get_interface(self, I_CONTAINER))) error(ERR_TYPE("IContainer"));

  return i->getElementType(_IContainer);
}

size_t count(const void* const _IContainer) {
  const Class* const* self = _IContainer;
  if (!_IContainer || !(*self)) error(ERR_NULLREF);
  IContainer* i = NULL;
  if (!(i = get_interface(self, I_CONTAINER))) error(ERR_TYPE("IContainer"));

  return i->count(_IContainer);
}

int is_empty(const void* const _IContainer) {
  // Relying `count`.
  return count(_IContainer) == 0;
}

int contains(const void* const _IContainer, const void* obj) {
  const Class* const* self = _IContainer;
  if (!_IContainer || !(*self)) error(ERR_NULLREF);
  IContainer* i = NULL;
  if (!(i = get_interface(self, I_CONTAINER))) error(ERR_TYPE("IContainer"));

  return i->contains(_IContainer, obj);
}

int some(const void* const _IContainer, int (*filter)(const void* element)) {
  const Class* const* self = _IContainer;
  if (!_IContainer || !(*self)) error(ERR_NULLREF);
  IContainer* i = NULL;
  if (!(i = get_interface(self, I_CONTAINER))) error(ERR_TYPE("IContainer"));

  return i->some(_IContainer, filter);
}

int every(const void* const _IContainer, int (*filter)(const void* element)) {
  const Class* const* self = _IContainer;
  if (!_IContainer || !(*self)) error(ERR_NULLREF);
  IContainer* i = NULL;
  if (!(i = get_interface(self, I_CONTAINER))) error(ERR_TYPE("IContainer"));

  return i->every(_IContainer, filter);
}
