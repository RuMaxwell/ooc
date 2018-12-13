#include "../header/String.h"

extern const void * string;

static void * String_constructor(void * _self, va_list * app) {
  String * self = _self;
  const char * chs = va_arg(*app, const char *);

  self->length = strlen(chs);
  self->chs = malloc(self->length + 1);

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

  if (!other || !is_instance(other, string))
    return 2;

  return strcmp(self->chs, other->chs);
}

static void * String_to_string(const void * _self) {
  return String_clone(_self);
}

static size_t String_ISequential_length(void * _self) {
  const String * self = _self;
  return self->length;
}

static void * String_ISequential_concat(void * _self, void * _other) {
  const String * self = _self;
  const String * other = _other;

  if (!_other || !(other->class))
    error(ERR_NULLREF);
  if (!is_instance(other, string))
    error(ERR_TYPE("string"));

  String * r = new(string, "");
  r->length = self->length + other->length;
  free(r->chs); r->chs = NULL;
  r->chs = malloc(r->length + 1);
  r->chs[0] = '\0';
  strcat(r->chs, self->chs);
  strcat(r->chs, other->chs);
  return r;
}

static const ISequential _string_i_sequential = {
  /* magic */ I_SEQUENTIAL,
  /* length */ String_ISequential_length,
  /* concat */ String_ISequential_concat
};

static const Interface _string_interfaces = {
  // 0
  (void *)(& _string_i_sequential),
  NULL
};

static const Class _string = {
  /* size */ sizeof (String),
  /* description */ "String",
  /* interfaces */ (Interface *)(& _string_interfaces),
  /* constructor */ String_constructor,
  /* destructor */ String_destructor,
  /* clone */ String_clone,
  /* differ */ String_differ,
  /* to_String */ String_to_string
};

const void * string = & _string;


//////// METHODS ////////

char * c_str(const void * _self) {
  const String * self = _self;

  if (!_self || !(self->class))
    error(ERR_NULLREF);

  if (!is_instance(self, string))
    error(ERR_TYPE("String"));

  return self->chs;
}
