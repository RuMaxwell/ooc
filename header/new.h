/* Object model

  ptr      prototype             class (type descripter)

   p -> [void * class] -> [             size_t size            ]
        [     ...    ]    [void*(*)(void*, va_list) constructor]
                          [void (*)(void*)          destructor ]
                          [void*(*)(void*)          clone      ]
                          [int  (*)(void*, void*)   differ     ]

  An object pointer is in fact a Class** variable.
*/

#ifndef _NEW_H
#define _NEW_H

#include "error.h"
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>

#define _THROWS // function that throws error (used at the end of a header function declaration)
#define _NO_THROW // function that do not throw error (used at the end of a header function declaration)
#define _CONST_METHOD // function that do not modify the first object pointer (used after a member function pointer)
#define _PRIVATE_METHOD // function that only declared and defined in the source file but not visible in the header file

#define var void *

typedef struct Interface {
  void * interface;
  struct Interface * next;
} Interface;

typedef struct Class {
  // the size of the class object
  size_t size;
  // a repeatable string for a class
  const char * description;
  // the list of interfaces implemented by the type
  const Interface * interfaces;

  // constructor takes a type descripter and an argument list, calls the type's constructor with the argument list, and returns the constructed object.
  void * (* constructor)(void * const _self, va_list * app);
  // destructor takes an object and calls its own destructor.
  void * (* destructor)(void * const _self);
  // clone takes an object, calls its own clone method and returns a cloned object. clone shall always create a new object.
  void * (* clone)(const void * const _self) _CONST_METHOD;
  // differ takes two objects, returns if the objects differs (according to the object's class's own differ method).
  int (* differ)(const void * const _self, const void * _other) _CONST_METHOD;
  // Returns a string representation of the object.
  void * (* to_string)(const void * const _self) _CONST_METHOD;
} Class;

// Create a new instace.
//// WILL throw an erjror if failed to allocate memory.
//// void * obj = new(Object, constructor_args)
void * new(const void * _Type, ...) _THROWS;

// Recycle the space used by an object.
//// Will NOT throw error when the argument is NULL or the argument is not a valid object.
//// delete(obj)
void delete(void * const _self) _NO_THROW;

// Returns a new object with the same class and the same type-specific data.
//// WILL throw an error when the first argument is NULL, or no class at the beginning of the object, or no clone (+2*(sizeof(void*)) offset) function pointer.
//// void * obj2 = clone(obj1);
void * clone(const void * const _self) _THROWS;

// Returns whether the two objects differs (according to the first object's differ method).
//// WILL throw an error when the first argument is NULL, or no class at the beginning of the object, or no differ (+3*(sizeof(void*)) offset) function pointer.
//// if (differ(a, b)) { ... }
int differ(const void * const _self, const void * _other) _THROWS;

// Returns the size.
//// WILL throw an error when the first argument is NULL, or no class at the beginning of the object.
size_t size_of(const void * const _self) _THROWS;

// Returns a string representation of the object.
//// By default, this uses the `def_to_string` function to return the description of the class. To enable this, just provide a `NULL` to the `to_string` function pointer when defining a type.
//// WILL throw an error when the first argument is NULL, or no class at the beginning of the object.
void * to_string(const void * const _self) _THROWS;


// Returns whether an object is an instance of the given class.
//// WILL throw an error when the first argument is NULL, or no class at the beginning of the object.
int is_instance(const void * const _self, const void * _class) _THROWS;

// Returns whether a class has implemented the given interface.
//// WILL throw an error when the first argument is NULL.
int implemented(const void * _class, const int interface) _THROWS;

// Returns the specific interface object when the class has implemented the given interface.
//// WILL throw an error when the first argument is NULL.
void * get_interface(const void * _class, const int interface) _THROWS;


//////// Garbage Collection ////////
void clear_objects() _NO_THROW;

#endif // !_NEW_H
