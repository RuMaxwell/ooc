#include "../header/console.h"

void putstr(const void * _string) {
  if (!is_instance(_string, string))
    error(ERR_TYPE("string"));

  printf("%s", c_str(_string));
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
