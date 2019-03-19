#ifndef _I_SEQUENTIAL_H
#define _I_SEQUENTIAL_H

#include "./new.h"

#define ERR_NO_HEAD "index error: Cannot retrieve head from an empty sequence."
#define ERR_NO_POP "index error: Cannot pop from an empty sequence."

#define I_SEQUENTIAL 0x13051114

typedef struct ISequential {
  const int magic;
  // Get the length of the sequence.
  size_t (* length)(const void * const _self);
  // Get the first element of the sequence.
  void * (* head)(const void * const _self);
  // Get a sequence only without the first element.
  void * (* tail)(const void * const _self);
  // Get an element at the specific index from the sequence.
  void * (* get)(const void * const _self, size_t index);
  // Set an element at the specific index in the sequence.
  void (* set)(void * const _self, size_t index, void * _object);
  // Insert an element at the specific index.
  size_t (* insert)(void * const _self, size_t index, const void * _object);
  // Remove the element at the specific index.
  void * (* drop)(void * const _self, size_t index);
  // Concatinate a sequence onto the end of a sequence.
  void * (* append)(void * const _self, const void * _other);
} ISequential;

size_t length(const void * const _self);
void * head(const void * const _self);
void * tail(const void * const _self);
void * get(const void * const _self, size_t index);
void set(void * const _self, size_t index, void * _object);
size_t insert(void * const _self, size_t index, const void * _object);
void * drop(void * const _self, size_t index);
void * append(void * const _self, const void * _other);

/* Automatic Implementation */
// Add an element at the end of a sequence.
size_t push(void * const _self, const void * _object);
// Remove the element at the end of a sequence.
void * pop(void * const _self);
// Get the concatination of two sequences of the same type.
void * concat(const void * const _self, const void * _other);

#endif
