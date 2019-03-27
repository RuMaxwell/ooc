#include "../header/Matrix.h"

extern const void* matrix;

typedef struct cell {
  void* data;
} cell;

typedef struct Matrix {
  const void* class;
  cell** data;
  size_t rows;
  size_t cols;
} Matrix;

static void* Matrix_constructor(void* const _self, va_list* app) {
  Matrix* const self = _self;
  size_t rows = va_arg(*app, size_t);
  size_t cols = va_arg(*app, size_t);

  self->data = NULL;
  self->rows = rows > 0 ? rows : 0;
  self->cols = cols > 0 ? cols : 0;
  if (self->rows == 0 || self->cols == 0) return self;

  self->data = calloc(1, rows * sizeof (cell*));
  for (size_t i = 0; i < rows; i++) {
    self->data[i] = calloc(1, cols * sizeof (cell));
  }

  return self;
}

static void* Matrix_destructor(void* const _self) {
  Matrix* const self = _self;

  fill(self, NULL);
  for (size_t i = 0; i < self->rows; i++) {
    if (self->data[i]) { free(self->data[i]), self->data[i] = NULL; }
  }
  if (self->data) free(self->data);
}

static void* Matrix_clone(const void* const _self) {
  const Matrix* const self = _self;
  Matrix* p = new(matrix, self->rows, self->cols);

  for (size_t i = 0; i < self->rows; i++)
    for (size_t j = 0; j < self->cols; j++)
      p->data[i][j].data = getMData(self, i, j);

  return p;
}

static int Matrix_differ(const void* const _self, const void* _other) {
  if (_self == _other) return 0;
  if (!_other || !(is_instance(_other, matrix))) return 2;

  const Matrix* const self = _self;
  const Matrix* other = _other;

  if (self->rows != other->rows || self->cols != other->cols)
    return 1;
  for (size_t i = 0; i < self->rows; i++)
    for (size_t j = 0; j < self->cols; j++)
      if (getMData(other, i, j) != getMData(self, i, j))
        return 1;
  return 0;
}

static void* Matrix_to_string(const void* const _self) {
  const Matrix* const self = _self;
  void* s = S("");

  for (size_t i = 0; i < self->rows; i++) {
    for (size_t j = 0; j < self->cols; j++) {
      void* dt = getMData(self, i, j);
      void* es;
      if (dt == NULL)
        es = S("(empty)");
      else
        es = to_string(dt);
      append(s, es);
      push(s, CHAR(' '));
      delete(es);
    }
    push(s, CHAR('\n'));
  }

  return s;
}

/* IArithmetic */
static void* Matrix_IArithmetic_add(void* const _self, const void* _other) {
  Matrix* const self = _self;
  const Matrix* other = _other;

  if (self->rows != other->rows || self->cols != other->cols)
    error(ERR_VALUE("Expected two matrices of the same size."))

  for (size_t i = 0; i < self->rows; i++)
    for (size_t j = 0; j < self->cols; j++) {
      void* n = plus(getMData(self, i, j), getMData(other, i, j));
      setMData(self, i, j, n);
    }

  return self;
}

static void* Matrix_IArithmetic_subtract(void* const _self, const void* _other) {
  Matrix* const self = _self;
  const Matrix* other = _other;

  if (self->rows != other->rows || self->cols != other->cols)
    error(ERR_VALUE("Expected two matrices of the same size."))

  for (size_t i = 0; i < self->rows; i++)
    for (size_t j = 0; j < self->cols; j++) {
      void* n = minus(getMData(self, i, j), getMData(other, i, j));
      setMData(self, i, j, n);
    }

  return self;
}

static void* Matrix_IArithmetic_plus(const void* const _self, const void* _other) {
  const Matrix* const self = _self;
  const Matrix* other = _other;

  if (self->rows != other->rows || self->cols != other->cols)
    error(ERR_VALUE("Expected two matrices of the same size."))

  Matrix* m = new(matrix, self->rows, self->cols);

  for (size_t i = 0; i < self->rows; i++)
    for (size_t j = 0; j < self->cols; j++)
      setMData(m, i, j, plus(getMData(self, i, j), getMData(other, i, j)));

  return m;
}

static void* Matrix_IArithmetic_minus(const void* const _self, const void* _other) {
  const Matrix* const self = _self;
  const Matrix* other = _other;

  if (self->rows != other->rows || self->cols != other->cols)
    error(ERR_VALUE("Expected two matrices of the same size."))

  Matrix* m = new(matrix, self->rows, self->cols);

  for (size_t i = 0; i < self->rows; i++)
    for (size_t j = 0; j < self->cols; j++)
      setMData(m, i, j, minus(getMData(self, i, j), getMData(other, i, j)));

  return m;
}

static const void* Matrix_IContainer_getElementType(const void* const _self) {
  const Matrix* const self = _self;
  if (self->cols == 0 || self->rows == 0 || some(_self, is_null))
    return any;

  size_t i, j;
  const void* type = get_class(getMData(self, 0, 0));
  for (i = 0; i < self->rows; i++)
    for (j = 0; j < self->cols; j++)
      if (get_class(getMData(self, i, j)) != type)
        return any;
  return type;
}

static size_t Matrix_IContainer_count(const void* const _self) {
  const Matrix* const self = _self;

  size_t i, j, count = 0;
  for (i = 0; i < self->rows; i++)
    for (j = 0; j < self->cols; j++)
      count += getMData(self, i, j) == NULL ? 0 : 1;

  return count;
}

static int Matrix_IContainer_contains(const void* const _self, const void* obj) {
  const Matrix* const self = _self;

  size_t i, j;
  for (i = 0; i < self->rows; i++)
    for (j = 0; j < self->cols; j++)
      if (getMData(self, i, j) == obj)
        return 1;
  return 0;
}

static int Matrix_IContainer_some(const void* const _self, int (*filter)(const void* element)) {
  const Matrix* const self = _self;

  size_t i, j;
  for (i = 0; i < self->rows; i++)
    for (j = 0; j < self->cols; j++)
      if (filter(getMData(self, i, j)))
        return 1;
  return 0;
}

static int Matrix_IContainer_every(const void* const _self, int (*filter)(const void* element)) {
  const Matrix* const self = _self;

  size_t i, j;
  for (i = 0; i < self->rows; i++)
    for (j = 0; j < self->cols; j++)
      if (!filter(getMData(self, i, j)))
        return 0;
  return 1;
}

static const IArithmetic _matrix_i_arithmetic = {
  .magic = I_ARITHMETIC,
  .add = Matrix_IArithmetic_add,
  .subtract = Matrix_IArithmetic_subtract,
  .plus = Matrix_IArithmetic_plus,
  .minus = Matrix_IArithmetic_minus
};
static const IContainer _matrix_i_container = {
  .magic = I_CONTAINER,
  .getElementType = Matrix_IContainer_getElementType,
  .count = Matrix_IContainer_count,
  .contains = Matrix_IContainer_contains,
  .some = Matrix_IContainer_some,
  .every = Matrix_IContainer_every
};

static const Interface _matrix_interfaces_1 = {
  (void*)(&_matrix_i_container),
  NULL
};
static const Interface _matrix_interfaces = {
  (void*)(&_matrix_i_arithmetic),
  (void*)(&_matrix_interfaces_1)
};

static const Class _matrix = {
  .size = sizeof (Matrix),
  .description = "matrix",
  .interfaces = &_matrix_interfaces,
  .constructor = Matrix_constructor,
  .destructor = Matrix_destructor,
  .clone = Matrix_clone,
  .differ = Matrix_differ,
  .to_string = Matrix_to_string
};

const void* matrix = &_matrix;


//////// METHODS ////////

size_t rows(const void* const _self) {
  if (!is_instance(_self, matrix))
    error(ERR_TYPE("Expected a matrix."))

  const Matrix* const self = _self;
  return self->rows;
}

size_t cols(const void* const _self) {
  if (!is_instance(_self, matrix))
    error(ERR_TYPE("Expected a matrix."))

  const Matrix* const self = _self;
  return self->cols;
}

void* getMData(const void* const _self, size_t r, size_t c) {
  if (!is_instance(_self, matrix))
    error(ERR_TYPE("Expected a matrix."))

  const Matrix* const self = _self;

  if (r < 0 || r >= self->rows || c < 0 || c >= self->cols)
    error(ERR_INDEX)

  return self->data[r][c].data;
}

void setMData(void* const _self, size_t r, size_t c, void* value) {
  if (!is_instance(_self, matrix))
    error(ERR_TYPE("Expected a matrix."))

  Matrix* const self = _self;

  if (r < 0 || r >= self->rows || c < 0 || c >= self->cols)
    error(ERR_INDEX)

  self->data[r][c].data = value;
}

void fill(void* const _self, void* value) {
  if (!is_instance(_self, matrix))
    error(ERR_TYPE("Expected a matrix."))

  Matrix* const self = _self;
  for (size_t i = 0; i < self->rows; i++) {
    for (size_t j = 0; j < self->cols; j++) {
      setMData(self, i, j, value);
    }
  }
}

void* mInverse(const void* const _self) {
  error(ERR_NOTIMPLEMENTED);
}
void* mTranspose(const void* const _self) {
  error(ERR_NOTIMPLEMENTED);
}

void* mMultiply(const void* const _self, const void* _other) {
  const Matrix* const self = _self;
  const Matrix* other = _other;
  if (!_self || !(self->class) || !_other || !(other->class))
    error(ERR_NULLREF)
  if (self->class != matrix || other->class != matrix)
    error(ERR_TYPE("matrix"))

  // Check dimensions
  if (self->cols != other->rows)
    error(ERR_VALUE("mMultiply: Matrices dimensions unmatched."))

  Matrix* res = new(matrix, self->rows, other->cols);

  const void* elemType = getElementType(self);
  if (elemType == any)
    error(ERR_VALUE("mMultiply: Elements should be the same type of IArithmetic and INumeric."))

  // Plain matrix multiplication  O(n^3)
  size_t i, j, k;
  void* sumvalue;
  for (i = 0; i < self->rows; i++)
    for (j = 0; j < other->cols; j++) {
      sumvalue = zero(elemType);
      for (k = 0; k < self->cols; k++) {
        void* thisvalue = times(getMData(self, i, k), getMData(other, k, j));
        add(sumvalue, thisvalue);
        delete(thisvalue), thisvalue = NULL;
      }
      setMData(res, i, j, sumvalue);
    }

  return res;
}
