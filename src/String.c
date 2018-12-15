#include "../header/String.h"

extern const void * string;

typedef struct String  {
  const void * class;
  size_t length;
  char * chs;
} String;


static void * String_constructor(void * const _self, va_list * app) {
  String * self = _self;
  const char * chs = va_arg(*app, const char *);

  self->length = strlen(chs);
  self->chs = malloc(self->length + 1);

  if (!(self->chs))
    error(ERR_MALLOC);

  strcpy(self->chs, chs);
  return self;
}

static void * String_destructor(void * const _self) {
  String * self = _self;

  free(self->chs), self->chs = NULL;

  return self;
}

static void * String_clone(const void * const _self) {
  const String * self = _self;
  return new(string, self->chs);
}

static int String_differ(const void * const _self, const void * _other) {
  const String * self = _self;
  const String * other = _other;

  if (self == other)
    return 0;

  if (!other || !is_instance(other, string))
    return 2;

  return strcmp(self->chs, other->chs);
}

static void * String_to_string(const void * const _self) {
  return String_clone(_self);
}

/* ISequential */
// String is special for its element type is char, not an object.
static size_t String_ISequential_length(const void * const _self) {
  const String * self = _self;
  return self->length;
}

static void * String_ISequential_head(const void * const _self) {
  const String * self = _self;
  return (void *)(int)(self->chs[0]);
}

static void * String_ISequential_tail(const void * const _self) {
  const String * self = _self;
  return new(string, (self->chs + 1));
}

static void * String_ISequential_get(const void * const _self, size_t index) {
  const String * self = _self;
  return (void *)(int)(self->chs[index]);
}

static void String_ISequential_set(void * const _self, size_t index, void * _object) {
  const String * self = _self;
  char c = (int)_object;
  self->chs[index] = c;
}

static size_t String_ISequential_push(void * const _self, const void * _object) {
  String * self = _self;
  char c = (int)_object;
  char * str = malloc(self->length + 2);
  strcpy(str, self->chs);
  str[self->length] = c;
  str[self->length + 1] = '\0';
  free(self->chs);
  self->chs = str;
  self->length++;
  return self->length;
}

static void * String_ISequentail_pop(void * const _self) {
  String * self = _self;
  char c = self->chs[self->length - 1];
  self->chs[self->length - 1] = '\0';
  self->length--;
  return (void *)(int)c;
}

static void * String_ISequentail_append(void * const _self, const void * _other) {
  String * self = _self;
  const String * other = _other;

  if (!is_instance(other, string))
    error(ERR_TYPE("string"));

  char * str = malloc(self->length + other->length + 1);
  strcpy(str, self->chs);
  strcat(str, other->chs);
  free(self->chs);
  self->chs = str;
  self->length += other->length;
}

static void * String_ISequential_concat(const void * const _self, const void * _other) {
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
  /* head */ String_ISequential_head,
  /* tail */ String_ISequential_tail,
  /* get */ String_ISequential_get,
  /* set */ String_ISequential_set,
  /* push */ String_ISequential_push,
  /* pop */ String_ISequentail_pop,
  /* append */ String_ISequentail_append,
  /* concat */ String_ISequential_concat
};

static const Interface _string_interfaces = {
  (void *)(& _string_i_sequential),
  NULL
};

static const Class _string = {
  /* size */ sizeof (String),
  /* description */ "string",
  /* interfaces */ & _string_interfaces,
  /* constructor */ String_constructor,
  /* destructor */ String_destructor,
  /* clone */ String_clone,
  /* differ */ String_differ,
  /* to_string */ String_to_string
};

const void * string = & _string;


//////// METHODS ////////

char * c_str(const void * const _self) {
  const String * self = _self;

  if (!_self || !(self->class))
    error(ERR_NULLREF);

  if (!is_instance(self, string))
    error(ERR_TYPE("String"));

  return self->chs;
}
