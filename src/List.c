#include "../header/List.h"

extern const void * list;

struct list_node {
  void * object;
  struct list_node * prev;
  struct list_node * next;
};

typedef struct List {
  const void * class;
  size_t length;
  struct list_node * head;
  struct list_node * last;
} List;


struct list_node * new_list_node(const void * object) {
  struct list_node * p = calloc(1, sizeof (struct list_node));
  if (!p) error(ERR_MALLOC);
  p->object = (void *)object;
  return p;
}

// Remove one list node from a list (by linking its previous and next nodes and free itself).
void remove_list_node(struct list_node * node) {
  struct list_node * p = node;
  if (node->prev) node->prev->next = p->next;
  if (node->next) node->next->prev = p->prev;
  p->object = NULL; // Destroy a list node shall not remove the referenced object, so just put this to NULL.
  free(p);
}

static void * List_constructor(void * const _self, va_list * _) {
  List * self = _self;
  self->length = 0;
  self->head = NULL;
  self->last = NULL;
  return self;
}

static void * List_destructor(void * const _self) {
  List * self = _self;
  struct list_node * p = self->head;
  if (!p) return self;

  struct list_node * q = p->next;
  for (; p != NULL; p = q) {
    remove_list_node(p);
    p = q;
    if (q) q = q->next;
  }

  return self;
}

static void * List_clone(const void * const _self) {
  const List * self = _self;
  List * p = new(list);
  const struct list_node * n = self->head;

  for (int i = 0; i < self->length; i++) {
    push(p, n->object);
    n = n->next;
  }

  return p;
}

static int List_differ(const void * const _self, const void * _other) {
  const List * self = _self;
  const List * other = _other;

  if (self->length != other->length)
    return !!(self->length - other->length);

  struct list_node * p = self->head;
  struct list_node * q = other->head;
  for (int i = 0; i < self->length; i++) {
    if (p->object != q->object) {
      return 1;
    }
  }
  return 0;
}

static void * List_to_string(const void * const _self) {
  const List * self = _self;
  void * s = S("[");
  if (self->length <= 0) {
    push(s, (void *)(int)']');
    return s;
  }

  struct list_node * p = self->head;
  for (; p->next != NULL; p = p->next) {
    void * obj_str = to_string(p->object);
    append(s, obj_str);
    delete(obj_str);
    push(s, (void *)',');
  }
  void * obj_str = to_string(p->object);
  append(s, obj_str);
  delete(obj_str);
  push(s, (void *)(int)']');

  return s;
}


static size_t List_ISequential_length(const void * const _self) {
  const List * self = _self;
  return self->length;
}

static void * List_ISequential_head(const void * const _self) {
  const List * self = _self;
  return self->head;
}

static void * List_ISequential_tail(const void * const _self) {
  const List * self = _self;
  List * p = List_clone(self);
  if (p->head) {
    p->head = p->head->next;
    p->length--;
  }
  return p;
}

static void * List_ISequence_get(const void * const _self, size_t index) {
  const List * self = _self;
  struct list_node * p = self->head;
  for (int i = 0; i < index; i++)
    p = p->next;
  return p->object;
}

static void List_ISequence_set(void * const _self, size_t index, void * _object) {
  const List * self = _self;
  struct list_node * p = self->head;
  for (int i = 0; i < index; i++)
    p = p->next;
  p->object = _object;
}

// static size_t List_ISequence_push(void * const _self, const void * _object) {
//   List * self = _self;

//   struct list_node * p = new_list_node(_object);
//   if (!self->head) {
//     self->head = p;
//     self->last = p;
//   } else {
//     self->last->next = p;
//     p->prev = self->last;
//     self->last = p;
//   }
//   self->length++;

//   return self->length;
// }

// static void * List_ISequence_pop(void * const _self) {
//   List * self = _self;

//   if (self->length <= 0)
//     error(ERR_INDEX);

//   struct list_node * p = self->last;
//   void * obj = p->object;
//   struct list_node * q = p->prev;
//   remove_list_node(p);
//   self->length--;
//   self->last = q;

//   return obj;
// }

static size_t List_ISequence_insert(void * const _self, size_t index, const void * _object) {
  List * self = _self;

  struct list_node * n = new_list_node(_object);

  if (index == self->length) {
    if (self->length == 0) {
      self->head = n;
      self->last = n;
    }
    self->last->next = n;
    n->prev = self->last;
    self->last = n;
  }
  else if (index == 0) {
    n->next = self->head;
    self->head->prev = n;
    self->head = n;
  }
  else {
    struct list_node * p = self->head;
    for (int i = 0; i < index; i++)
      p = p->next;
    n->next = p;
    n->prev = p->prev;
    p->prev->next = n;
    p->prev = n;
  }

  self->length++;
  return self->length;
}

static void * List_ISequence_drop(void * const _self, size_t index) {
  List * self = _self;

  if (index == self->length - 1) {
    void * obj = self->last->object;
    remove_list_node(self->last);
    self->length--;
    return obj;
  }
  else {
    struct list_node * p = self->head;
    for (int i = 0; i < index; i++)
      p = p->next;
    void * obj = p->object;
    remove_list_node(p);
    self->length--;
    return obj;
  }
}

static void * List_ISequence_append(void * const _self, const void * _other) {
  List * self = _self;
  const List * other = _other;

  if (!is_instance(other, list))
    error(ERR_TYPE("list"));

  struct list_node * n = other->head;
  for (int i = 0; i < other->length; i++) {
    List_ISequence_insert(self, self->length, n->object);
    self->length++;
    n = n->next;
  }

  return self;
}

static void * List_ISequential_concat(const void * const _self, const void * _other) {
  void * res = List_clone(_self);
  List_ISequence_append(res, _other);
  return res;
}

static void* List_IFunctor_map(const void* const _self, void* (*f)(const void*)) {
  const List* const self = _self;
  struct list_node* p = self->head;
  List* lst = new(list);

  for (; p != NULL; p = p->next)
    push(lst, f(p->object));

  return lst;
}

static void* List_IApplicative_apply(const void* const _self, const void* _other) {
  const List* const self = _self;
  const List* const other = _other;
  struct list_node* p = self->head;
  struct list_node* q = other->head;
  List* lst = new(list);

  for (; q != NULL; q = q->next)
    for (p = self->head; p != NULL; p = p->next) {
      void* (*f)(const void*) = q->object;
      push(lst, f(p->object));
    }

  return lst;
}

static const ISequential _list_i_sequential = {
  .magic = I_SEQUENTIAL,
  .length = List_ISequential_length,
  .head = List_ISequential_head,
  .tail = List_ISequential_tail,
  .get = List_ISequence_get,
  .set = List_ISequence_set,
  .insert = List_ISequence_insert,
  .drop = List_ISequence_drop,
  .append = List_ISequence_append,
};
static const IFunctor _list_i_functor = {
  .magic = I_FUNCTOR,
  .map = List_IFunctor_map
};
static const IApplicative _list_i_applicative = {
  .magic = I_APPLICATIVE,
  .apply = List_IApplicative_apply
};

static const Interface _list_interfaces_2 = {
  (void*)(&_list_i_applicative),
  NULL
};
static const Interface _list_interfaces_1 = {
  (void*)(&_list_i_functor),
  (void*)(&_list_interfaces_2)
};
static const Interface _list_interfaces = {
  (void*)(&_list_i_sequential),
  (void*)(&_list_interfaces_1)
};

static const Class _list = {
  .size = sizeof (List),
  .description = "list",
  .interfaces = & _list_interfaces,
  .constructor = List_constructor,
  .destructor = List_destructor,
  .clone = List_clone,
  .differ = List_differ,
  .to_string = List_to_string
};

const void * list = & _list;


//////// METHODS ////////

void * LIST(int count, ...) {
  va_list ap;
  va_start(ap, count);
  void * p = new(list);
  void * obj = NULL;
  for (int i = 0; i < count; i++) {
    obj = va_arg(ap, void *);
    push(p, obj);
  }
  va_end(ap);
  return p;
}
