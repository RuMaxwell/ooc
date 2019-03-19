#ifndef _ERROR_H
#define _ERROR_H

#include <assert.h>
#include <stdio.h>

#define ERR_NOTIMPLEMENTED "Not implemented!"
#define ERR_INDEX "index error: Index out of range."
#define ERR_MALLOC "malloc error: Failed to allocate memory."
#define ERR_NULLREF "null reference error: Object pointer is null."
#define ERR_TYPE(TYPE) "type error: Expected a(an) " TYPE " object."
#define ERR_VALUE(Msg) "value error: " Msg

#ifndef NON_MACRO_ERROR
  #define error(message) { fprintf(stderr, "%s\n", message); assert(0); }
#else
  void error(const char * message) {
    fprintf(stderr, "%s\n", message);
    assert(0);
  }
#endif

#endif
