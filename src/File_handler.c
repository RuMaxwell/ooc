#include "../header/File_handler.h"

extern const void * file_handler;

typedef struct File_handler {
  const void * class;
  char * file_name;
  FILE * file_ptr;
} File_handler;

static void * File_handler_constructor(void * const _self, va_list * app) {
  File_handler * self = _self;
  const char * file_name = va_arg(*app, const char *);

  self->file_name = malloc(strlen(file_name));

  if (!(self->file_name))
    error(ERR_MALLOC);

  strcpy(self->file_name, file_name);
  self->file_ptr = NULL;

  return self;
}

static void * File_handler_destructor(void * const _self) {
  File_handler * self = _self;
  if (fopen(self->file_name, "r"))
    fclose(self->file_ptr);
  self->file_ptr = NULL;
  return self;
}

static void * File_handler_clone(const void * const _self) {
  // const File_handler * self = _self;
  // File_handler * p = new(file_handler, self->file_name);
  // p->file_ptr = self->file_ptr;
  // return p;
  return NULL;
}

static int File_handler_differ(const void * const _self, const void * _other) {
  return _self != _other;
}

static void * File_handler_to_string(const void * const _self) {
  const File_handler * self = _self;
  void * file_name = S(self->file_name);
  void * descripter = S("<file handler: ");
  append(descripter, file_name);
  push(descripter, (void *)(int)'>');
  delete(file_name);
  return descripter;
}

static const Class _file_handler = {
  .size = sizeof (File_handler),
  .description = "file_handler",
  .interfaces = NULL,
  .constructor = File_handler_constructor,
  .destructor = File_handler_destructor,
  .clone = File_handler_clone,
  .differ = File_handler_differ,
  .to_string = File_handler_to_string
};

const void * file_handler = & _file_handler;


//////// METHODS ////////

void * from_FILE_ptr(FILE * file, const char * file_name) {
  File_handler * p = new(file_handler, file_name);
  p->file_ptr = file;
  return p;
}

FILE * to_FILE_ptr(const void * const _self) {
  const File_handler * self = _self;
  return self->file_ptr;
}

void * read_file(void * const _self) {
  File_handler * self = _self;

  if (!(self->file_ptr)) {
    self->file_ptr = fopen(self->file_name, "r");
    if (!(self->file_ptr))
      error(ERR_OPEN_FILE);
  }

  char * buffer[512];
  void * res = S("");
  while (fread(buffer, 1, 512, self->file_ptr) > 0) {
    void * str = new(string , buffer);
    append(res, str);
    delete(str);
  }

  fclose(self->file_ptr);
  self->file_ptr = NULL;

  return res;
}

void write_file(void * const _self, const void * _string) {
  File_handler * self = _self;

  if (!(self->file_ptr)) {
    self->file_ptr = fopen(self->file_name, "w");
    if (!(self->file_ptr))
      error(ERR_OPEN_FILE);
  }

  if (!is_instance(_string, string))
    error(ERR_TYPE("string"));

  size_t len = length(_string);
  char * buffer = c_str(_string);
  for (int i = 0; i <= len / 512; i++) {
    fprintf(self->file_ptr, "%s", buffer);
  }

  fclose(self->file_ptr);
  self->file_ptr = NULL;
}
