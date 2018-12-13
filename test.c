#include "header/Object.h"
#include "header/String.h"
#include "header/Console.h"

#include <stdio.h>

int main(int argc, char const * argv[]) {
  void * obj = new(object);
  void * hello = new(string, "Hello, world");
  void * obj_str = to_string(obj);

  print(obj);
  print(hello);
  putstrln(obj_str);

  printf("%s = %ld\n", c_str(hello), length(hello));
  void * cat_str = concat(hello, obj_str);
  printf("%s = %ld\n", c_str(cat_str), length(cat_str));

  clear_objects();
  return 0;
}

