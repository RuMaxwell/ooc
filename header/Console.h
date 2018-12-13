#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "./new.h"
#include "./String.h"

// Print a string object, without appending a line break.
//// WILL throw an error if the argument is not a string object.
void putstr(const void * _string) _THROWS;

// Print a string object and break the current line.
//// WILL throw an error if the argument is not a string object.
void putstrln(const void * _string) _THROWS;

// Print an object by calling its to_string method.
void print(const void * _object) _NO_THROW;

#endif
