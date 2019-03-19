#include "../header/new.h"

extern const void * string;

//////// Garbage Collection ////////
struct object_node {
  void * object;
  // int reference_count;
  struct object_node * next;
};
static struct object_node * _nodes = NULL;
static void push_node(const void * _object);
static void pop_node();
static struct object_node * find_node(void * _object);
// static void remove_node(struct object_node * _node);

// bind(str, S("a string"));
// bind(str1, str);
// #define bind(name, obj)\
//   void * name = obj;\
//   {\
//     struct object_node * n = find_node(name);\
//     if (!n) { push_node(name); runtime_objects->reference_count++; }\
//     else { n->reference_count++; }\
//   }

// #define unbind(name)\
//   {\
//     struct object_node * n = find_node(name);\
//     if (!n) { name = NULL; }\
//     else {\
//       n->reference_count--;\
//       if (n->reference_count <= 0) { delete(n->object); remove_node(n); }\
//     }\
//   }

// Create a new instace.
//// WILL throw an error if failed to allocate memory.
void * new(const void * _Type, ...) {
  const Class * Type = _Type; // convert void* to Class
  void * p = calloc(1, Type->size); // take the size field of the class

  if (!p)
    error(ERR_MALLOC); // stop the program if failed to allocate memory

  * (const Class **) p = Type; // make the object as a pointer to the class pointer
  /* p -> [void * class] -> [             size_t size            ]
          [     ...    ]    [void*(*)(void*, va_list) constructor]
                            [void (*)(void*)          destructor ]
                            [void*(*)(void*)          clone      ]
                            [int  (*)(void*, void*)   differ     ]
  */

  if (Type->constructor) { // not a really significant judgement
    va_list ap;
    va_start(ap, _Type); // retrieve the rest arguments

    p = Type->constructor(p, & ap); // call the class's constructor to allocate space for its own use

    va_end(ap);
  }

  push_node(p); // GC

  return p; // return the pointer to the object
}

// Recycle the space used by an object.
//// Will NOT throw error when the argument is NULL or the argument is not a valid object.
void delete(void * const _self) {
  Class ** object = _self; // convert the pointer into a valid object

  // garbage collection: finding the object node
  struct object_node * p = _nodes;
  struct object_node * q = NULL;
  for (; p; ) {
    if (p->object == object) {
      break;
    }
    q = p;
    p = p->next;
  }

  void * rem = NULL;
  if (object && *object && (*object)->destructor) { // current version only consider null pointers
    rem = (*object)->destructor(object); // call the class's own destructor to free the space created by its constructor
  }

  if (rem) {
    free(rem); // free the object itself to finish deletion

    // garbage collection: removing the node
    if (p) {
      p->object = NULL;
      if (q)
        q->next = p->next;
      else {
        pop_node();
      }
      free(p);
    }
  }
}

// Returns a new object with the same class and the same type-specific data.
//// WILL throw an error when the first argument is NULL, or no class at the beginning of the object, or no clone (+2*(sizeof(void*)) offset) function pointer.
void * clone(const void * const _self) {
  const Class * const * self = _self; // *self is a const pointer; self represents the object, *self represent the pointer to the class

  if (!_self || !(*self) || !((*self)->clone))
    error(ERR_NULLREF); // throw error

  return (*self)->clone(_self); // lately binds the object's clone method
}

// Returns whether the two objects differs (according to the first object's differ method).
//// WILL throw an error when the first argument is NULL, or no class at the beginning of the object, or no differ (+3*(sizeof(void*)) offset) function pointer.
int differ(const void * const _self, const void * _other) {
  const Class * const * self = _self; // the same with clone()

  if (!_self || !(*self) || !((*self)->differ))
    error(ERR_NULLREF); // throw error

  return (*self)->differ(_self, _other); // lately binds the object's differ method
}

// Returns the size.
//// WILL throw an error when the first argument is NULL, or no class at the beginning of the object.
size_t size_of(const void * const _self) {
  const Class * const * self = _self; // the same with clone()

  if (!_self || !(*self))
    error(ERR_NULLREF);

  return (*self)->size;
}

// default `to_string` method to be used when the class does not provide its own `to_string` method
void * def_to_string(const void * const _self) _PRIVATE_METHOD {
  const Class * const * self = _self;

  if (!_self || !(*self))
    error(ERR_NULLREF);

  return new(string, (*self)->description);
}

// Returns a string representation of the object.
//// By default, this uses the `def_to_string` function to return the description of the class. To enable this, just provide a `NULL` to the `to_string` function pointer when defining a type.
//// WILL throw error when the first argument is NULL, or no class at the beginning of the object.
void * to_string(const void * const _self) {
  const Class * const * self = _self;

  if (!_self || !(*self)) {
    // char intconst[16];
    // itoa((int)self, intconst, 10);
    // return new(string, intconst);
    error(ERR_NULLREF);
  }

  return (*self)->to_string ? (*self)->to_string(_self) : def_to_string(_self);
}

// Returns whether an object is an instance of the given class.
//// WILL throw an error when the first argument is NULL, or no class at the beginning of the object.
int is_instance(const void * const _self, const void * _class) {
  const Class * const * self = _self;

  if (!_self || !(*self))
    error(ERR_NULLREF);

  return *self == _class;
}

// Returns whether a class has implemented the given interface.
//// WILL throw an error when the first argument is NULL.
int implemented(const void * _class, const int interface) {
  return get_interface(_class, interface) ? 1 : 0;
}

// Returns the specific interface object when the class has implemented the given interface.
//// WILL throw an error when the first argument is NULL.
void * get_interface(const void * _class, const int interface) {
  const Class * const * class = _class;

  if (!_class || !(*class))
    error(ERR_NULLREF);

  const Interface * p = (*class)->interfaces;
  for (; p != NULL; p = p->next) {
    if (* (int *)(p->interface) == interface) {
      return p->interface;
    }
  }
  return NULL;
}


////////////////////////////////////
//////// Garbage Collection ////////
////////////////////////////////////

static void push_node(const void * _object) {
  struct object_node * p = calloc(1, sizeof (struct object_node));
  p->object = (void *)_object;
  p->next = _nodes;
  _nodes = p;
}

static void pop_node() {
  if (_nodes)
    _nodes = _nodes->next;
}

static struct object_node * find_node(void * _object) {
  struct object_node * p = _nodes;
  for (; p; p = p->next) {
    if (p->object == _object) {
      return p;
    }
  }
}

void clear_objects() {
  struct object_node * p = _nodes;
  struct object_node * q = p;
  for (; p; ) {
    q = p->next;
    delete(p->object);
    p = q;
  }
}
