#include "../header/Object.h"
#include "../header/String.h"
#include "../header/ImmutableList.h"
#include "../header/List.h"
#include "../header/console.h"

#include <stdio.h>

void test_string() {
  void * obj = new(object);
  void * hello = new(string, "Hello, world");
  void * obj_str = to_string(obj);

  print(obj);
  print(hello);
  putstrln(obj_str);

  printf("%s = %ld\n", c_str(hello), length(hello));
  void * cat_str = concat(hello, obj_str);
  printf("%s = %ld\n", c_str(cat_str), length(cat_str));
}

void test_ulist() {
  void * lst = cons(
    new(string, "1"), cons(
    new(string, "2"), cons(
    new(string, "3"), cons(
    new(string, "4"), cons(
    new(string, "5"), new(ulist)
    )))));

  print(lst);
}

void test_list() {
  void * lst = new(list);
  push(lst, new(string, "1"));
  push(lst, new(string, "2"));
  push(lst, new(string, "3"));
  push(lst, new(string, "4"));
  push(lst, new(string, "5"));
  print(lst);
  void * str = pop(lst);
  print(str);
  print(lst);

  void * lst2 = clone(lst);
  append(lst2, lst);
  print(lst2);
}
