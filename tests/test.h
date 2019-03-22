#include "../header/Object.h"
#include "../header/String.h"
#include "../header/ImmutableList.h"
#include "../header/List.h"
#include "../header/Matrix.h"
#include "../header/Integer.h"
#include "../header/io.h"

#include <stdio.h>

void test_string() {
  var obj = new(object);
  var hello = S("Hello, world");
  var obj_str = to_string(obj);

  print(obj);
  print(hello);
  putstrln(obj_str);

  printf("%s = %ld\n", c_str(hello), length(hello));
  var cat_str = concat(hello, obj_str);
  printf("%s = %ld\n", c_str(cat_str), length(cat_str));
}

void test_ulist() {
  var lst = cons(
    S("1"), cons(
    S("2"), cons(
    S("3"), cons(
    S("4"), cons(
    S("5"), new(ulist)
    )))));

  print(lst);
}

void test_list() {
  var lst = LIST(5, S("1"), S("2"), S("3"), S("4"), S("5"));
  print(lst);
  var str = pop(lst);
  print(str);
  print(lst);

  var lst2 = clone(lst);
  append(lst2, lst);
  print(lst2);
}

void test_io() {
  var str0 = S("str0");
  var str1 = S("str1");
  var obj = new(object);

  printc(3, str0, str1, obj, obj);
  printcfg(STDOUT_COMMA_3, str0, str1, obj);
}

void test_file() {
  var txt = new(file_handler, "text1.txt");
  write_file(txt, S("Hello, world.\nIt's should be normal."));
  var newtxt = read_file(txt);
  print(newtxt);
  // FIXME:
  // var newnewtxt = read_file(STDIN_HANDLER);
  // print(newnewtxt);
}

void test_matrix() {
  var m = new(matrix, 3, 3);
  var one = I(1);
  var two = I(2);
  fill(m, one);
  print(m);
  setMData(m, 1, 1, two);
  print(m);

  var m1 = new(matrix, 3, 3);
  var zero = I(0);
  fill(m1, zero);
  setMData(m1, 1, 0, one);
  setMData(m1, 1, 2, one);
  add(m, m1);
  print(m1);
  print(m);
}
