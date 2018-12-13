#include "../header/String.h"

extern const void * string;

static void * String_constructor(void * _self, va_list * app) {
  String * self = _self;
  const char * chs = va_arg(*app, const char *);

  self->chs = malloc(strlen(chs) + 1);

  if (!(self->chs))
    error(ERR_MALLOC);

  strcpy(self->chs, chs);
  return self;
}

static void * String_destructor(void * _self) {
  String * self = _self;

  free(self->chs), self->chs = NULL;

  return self;
}

static void * String_clone(const void * _self) {
  const String * self = _self;
  return new(string, self->chs);
}

static int String_differ(const void * _self, const void * _other) {
  const String * self = _self;
  const String * other = _other;

  if (self == other)
    return 0;

  if (!other || other->class != string)
    return 2;

  return strcmp(self->chs, other->chs);
}

static void * String_to_string(const void * _self) {
  return String_clone(_self);
}

static const Class _string = {
  /* size */ sizeof (String),
  /* description */ "String",
  /* interfaces */ NULL,
  /* constructor */ String_constructor,
  /* destructor */ String_destructor,
  /* clone */ String_clone,
  /* differ */ String_differ,
  /* to_String */ String_to_string
};

const void * string = & _string;
