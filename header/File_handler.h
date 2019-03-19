#ifndef _FILE_HANDLER_H
#define _FILE_HANDLER_H

#include "./new.h"
#include "./String.h"
#include <stdio.h>
#include <string.h>

#define ERR_NO_FPTR "null reference error: No FILE pointer in the file handler."
#define ERR_OPEN_FILE "io error: Failed to open the file."

extern const void * file_handler;

#define STDIN_FILE ((void *)1)
#define STDOUT_FILE ((void *)2)
#define STDERR_FILE ((void *)3)

extern void * const STDIN_HANDLER;
extern void * const STDOUT_HANDLER;
extern void * const STDERR_HANDLER;

void * from_FILE_ptr(FILE * file, const char * file_name);
FILE * to_FILE_ptr(const void * const _self);

void * read_file(void * const _self);
void write_file(void * const _self, const void * _string);

#endif
