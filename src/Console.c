#include "../header/Console.h"

void putstr(const void * _string) {
  const String * str = _string;

  if (!is_instance(str, string))
    error(ERR_TYPE("string"));

  printf("%s", str->chs);
}

void putstrln(const void * _string) {
  putstr(_string);
  putchar('\n');
}

void print(const void * _object) {
  void * str = to_string(_object);
  putstrln(str);
  delete(str);
}
