#include "../header/Integer.h"

extern const void* integer;

typedef struct Integer {
  const void* class;
  int value;
} Integer;


static void* Integer_constructor(void* const _self, va_list* app) {
  Integer* const self = _self;
  int v = va_arg(*app, int);

  self->value = v;

  return self;
}

static void* Integer_destructor(void* const _self) {
  return _self;
}

static void* Integer_clone(const void* const _self) {
  const Integer* const self = _self;
  return new(integer, self->value);
}

static int Integer_differ(const void* const _self, const void* _other) {
  const Integer* const self = _self;
  const Integer* other = _other;
  return self->value - other->value;
}

static void* Integer_to_string(const void* const _self) {
  const Integer* const self = _self;
  char buffer[12];
  itoa(self->value, buffer, 10);
  return new(string, buffer);
}

static void* Integer_default_value() {
  return new(integer, 0);
}

/* IArithmetic */
static void* Integer_IArithmetic_zero() {
  return new(integer, 0);
}

static void* Integer_IArithmetic_add(void* const _self, const void* _other) {
  Integer* const self = _self;
  const Integer* other = _other;
  self->value += other->value;
  return self;
}

static void* Integer_IArithmetic_subtract(void* const _self, const void* _other) {
  Integer* const self = _self;
  const Integer* other = _other;
  self->value -= other->value;
  return self;
}

static void* Integer_IArithmetic_plus(const void* const _self, const void* _other) {
  const Integer* const self = _self;
  const Integer* other = _other;

  Integer* i = new(integer, self->value + other->value);
  return i;
}

static void* Integer_IArithmetic_minus(const void* const _self, const void* _other) {
  const Integer* const self = _self;
  const Integer* other = _other;

  Integer* i = new(integer, self->value - other->value);
  return i;
}

/* IComparable */
static int Integer_IComparable_compare(const void * const _self, const void * _other) {
  return differ(_self, _other);
}

/* INumeric */
static void* Integer_INumeric_identity() {
  return new(integer, 1);
}

static void* Integer_INumeric_multiply(void* const _self, const void* _other) {
  Integer* const self = _self;
  const Integer* other = _other;

  self->value *= other->value;
  return self;
}

static void* Integer_INumeric_times(const void* const _self, const void* _other) {
  const Integer* const self = _self;
  const Integer* other = _other;

  void* i = new(integer, self->value * other->value);
  return i;
}


static const IArithmetic _integer_i_arithmetic = {
  .magic = I_ARITHMETIC,
  .zero = Integer_IArithmetic_zero,
  .add = Integer_IArithmetic_add,
  .subtract = Integer_IArithmetic_subtract,
  .plus = Integer_IArithmetic_plus,
  .minus = Integer_IArithmetic_minus
};
static const IComparable _integer_i_comparable = {
  .magic = I_COMPARABLE,
  .compare = Integer_IComparable_compare
};
static const INumeric _integer_i_numeric = {
  .magic = I_NUMERIC,
  .identity = Integer_INumeric_identity,
  .multiply = Integer_INumeric_multiply,
  .times = Integer_INumeric_times
};

static const Interface _integer_interfaces_2 = {
  (void*)(&_integer_i_numeric),
  NULL
};
static const Interface _integer_interfaces_1 = {
  (void*)(&_integer_i_comparable),
  (void*)(&_integer_interfaces_2)
};
static const Interface _integer_interfaces = {
  (void*)(&_integer_i_arithmetic),
  (void*)(&_integer_interfaces_1)
};

static const Class _integer = {
  .size = sizeof (Integer),
  .description = "integer",
  .interfaces = &_integer_interfaces,
  .constructor = Integer_constructor,
  .destructor = Integer_destructor,
  .clone = Integer_clone,
  .differ = Integer_differ,
  .to_string = Integer_to_string,

  .default_value = Integer_default_value
};

const void* integer = &_integer;


//////// METHODS ////////

int int_value(const void* const _self) {
  const Integer* const self = _self;
  return self->value;
}

void set_int(void* const _self, const int value) {
  Integer* const self = _self;
  self->value = value;
}
