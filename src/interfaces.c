#include "../header/interfaces.h"

I_CONTAINER_METHOD void * concat(void * _a, void * _b) {
  const Class * const * a = _a;
  const Class * const * b = _b;

  if (!_a || !_b || !(*a) || !(*b))
    error(ERR_NULLREF);
  if (!implemented(a, I_CONTAINER))
    error(ERR_TYPE("IContainer"));

  //
}
