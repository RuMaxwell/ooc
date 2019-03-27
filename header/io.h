#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "./new.h"
#include "./File_handler.h"
#include "./String.h"

#define ERR_PRT_COUNT "value error: Not enough number of objects to be printed."

struct print_config {
  int count;
  char * end;
  char * splitter;
  void * file;
} Print_config;

extern struct print_config * STDOUT_1;
extern struct print_config * STDOUT_2;
extern struct print_config * STDOUT_3;
extern struct print_config * STDOUT_COMMA_2;
extern struct print_config * STDOUT_COMMA_3;
extern struct print_config * STDERR_1;
extern struct print_config * STDERR_2;
extern struct print_config * STDERR_3;
extern struct print_config * STDERR_COMMA_2;
extern struct print_config * STDERR_COMMA_3;
extern struct print_config * STDOUT_NB_1;
extern struct print_config * STDOUT_NSPL_NB_2;
extern struct print_config * STDOUT_NSPL_NB_3;
extern struct print_config * STDOUT_COMMA_NB_2;
extern struct print_config * STDOUT_COMMA_NB_3;

/*
 * Print a string object, without appending a line break.
 * WILL throw an error if the argument is not a string object.
 *   _string: string
 */
void putstr(const void * _string) _THROWS;

/*
 * Print a string object and break the current line.
 * WILL throw an error if the argument is not a string object.
 *   _string: string
 */
void putstrln(const void * _string) _THROWS;

/*
 * Print an object by calling its to_string method.
 *   _object: object
 */
void print(const void * _object) _NO_THROW;

/*
 * Print an object without adding a line break.
 *   _object: object
 */
void printnln(const void * _object);

/*
 * Print several objects. The number of the objects is indicated by `count`. The objects are seperated by a space.
 *   ...: object, object, ...
 */
void printc(int count, ...);

/*
 * Print an object to a file.
 *   file: file_handler
 *   _object: object
 */
void fprint(void * file, void * _object);

/*
 * Print an object to a file without adding a line break.
 *   file: file_handler
 *   _object: object
 */
void fprintnln(void * file, void * _object);

/*
 * Print several objects to a file. The number of the objects is indicated by `count`. The objects are seperated by a space.
 *   file: file_handler
 *   ...: object, object, ...
 */
void fprintc(void * file, int count, ...);

/*
 * Print several objects using in a specific format according to `config`.
 */
void printcfg(struct print_config * config, ...);

/*
 * Print several objects in format given by the format string.
 */
void printFormat(void * formatString, ...);

#endif
