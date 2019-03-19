#include "../header/io.h"

struct print_config _STDOUT_1 = { 1, "\n", " ", STDOUT_FILE };
struct print_config _STDOUT_2 = { 2, "\n", " ", STDOUT_FILE };
struct print_config _STDOUT_3 = { 3, "\n", " ", STDOUT_FILE };
struct print_config _STDOUT_COMMA_2 = { 2, "\n", ",", STDOUT_FILE };
struct print_config _STDOUT_COMMA_3 = { 3, "\n", ",", STDOUT_FILE };
struct print_config _STDERR_1 = { 1, "\n", " ", STDERR_FILE };
struct print_config _STDERR_2 = { 1, "\n", " ", STDERR_FILE };
struct print_config _STDERR_3 = { 1, "\n", " ", STDERR_FILE };
struct print_config _STDERR_COMMA_2 = { 2, "\n", ",", STDERR_FILE };
struct print_config _STDERR_COMMA_3 = { 3, "\n", ",", STDERR_FILE };
struct print_config _STDOUT_NB_1 = { 1, "", "", STDOUT_FILE };
struct print_config _STDOUT_NSPL_NB_2 = { 2, "", "", STDOUT_FILE };
struct print_config _STDOUT_NSPL_NB_3 = { 3, "", "", STDOUT_FILE };
struct print_config _STDOUT_COMMA_NB_2 = { 2, "", ",", STDOUT_FILE };
struct print_config _STDOUT_COMMA_NB_3 = { 3, "", ",", STDOUT_FILE };

struct print_config * STDOUT_1 = & _STDOUT_1;
struct print_config * STDOUT_2 = & _STDOUT_2;
struct print_config * STDOUT_3 = & _STDOUT_3;
struct print_config * STDOUT_COMMA_2 = & _STDOUT_COMMA_2;
struct print_config * STDOUT_COMMA_3 = & _STDOUT_COMMA_3;
struct print_config * STDERR_1 = & _STDERR_1;
struct print_config * STDERR_2 = & _STDERR_2;
struct print_config * STDERR_3 = & _STDERR_3;
struct print_config * STDERR_COMMA_2 = & _STDERR_COMMA_2;
struct print_config * STDERR_COMMA_3 = & _STDERR_COMMA_3;
struct print_config * STDOUT_NB_1 = & _STDOUT_NB_1;
struct print_config * STDOUT_NSPL_NB_2 = & _STDOUT_NSPL_NB_2;
struct print_config * STDOUT_NSPL_NB_3 = & _STDOUT_NSPL_NB_3;
struct print_config * STDOUT_COMMA_NB_2 = & _STDOUT_COMMA_NB_2;
struct print_config * STDOUT_COMMA_NB_3 = & _STDOUT_COMMA_NB_3;

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

void printnln(const void * _object) {
  void * str = to_string(_object);
  putstr(str);
  delete(str);
}

void printc(int count, ...) {
  va_list ap;
  va_start(ap, count);

  void * obj;
  for (int i = 0; i < count; i++) {
    obj = va_arg(ap, void *);
    if (!obj) error(ERR_PRT_COUNT);
    printnln(obj);
    putchar(' ');
  }
  putchar('\n');

  va_end(ap);
}

void fprint(void * file, void * _object) {
  void * str = to_string(_object);
  write_file(file, str);
  delete(str);
}

void printcfg(struct print_config * config, ...) {
  if (!config)
    return;

  va_list ap;
  va_start(ap, config);
  void * obj;
  if (config->file == STDOUT_FILE || config->file == STDERR_FILE) {
    int std = !!(config->file);
    for (int i = 0; i < config->count - 1; i++) {
      obj = va_arg(ap, void *);
      if (!obj) error(ERR_PRT_COUNT);
      printnln(obj);
      fprintf(std ? stderr : stdout, "%s", config->splitter);
    }
    obj = va_arg(ap, void *);
    if (!obj) error(ERR_PRT_COUNT);
    printnln(obj);
    fprintf(std ? stderr : stdout, "%s", config->end);
  } else {
    void * splitter = S(config->splitter);
    void * ending = S(config->end);
    for (int i = 0; i < config->count - 1; i++) {
      obj = va_arg(ap, void *);
      if (!obj) error(ERR_PRT_COUNT);
      // fprintnln(config->file, obj);
      // fprintnln(config->file, splitter);
    }
    // fprintnln(config->file, obj);
    // fprintnln(config->file, ending);
    delete(splitter); delete(ending);
  }
}
