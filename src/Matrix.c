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

  self->data = calloc(1, cols * sizeof (cell*));
  for (size_t i = 0; i < cols; i++) {
    self->data[i] = calloc(1, rows * sizeof (cell));
  }

  return self;
}

static void* Matrix_destructor(void* const _self) {
  Matrix* const self = _self;

  fill(self, NULL);
  for (size_t i = 0; i < self->cols; i++) {
    if (self->data[i]) { free(self->data[i]), self->data[i] = NULL; }
  }
  if (self->data) free(self->data);
}

static void* Matrix_clone(const void* const _self) {
  const Matrix* const self = _self;
  Matrix* p = new(matrix, self->rows, self->cols);

  for (size_t i = 0; i < self->rows; i++)
    for (size_t j = 0; j < self->cols; j++)
      p->data[i][j].data = self->data[i][j].data;

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
      if (other->data[i][j].data != self->data[i][j].data)
        return 1;
  return 0;
}

static void* Matrix_to_string(const void* const _self) {
  const Matrix* const self = _self;
  void* s = S("");

  for (size_t i = 0; i < self->rows; i++) {
    for (size_t j = 0; j < self->cols; j++) {
      void* es = to_string(self->data[i][j].data);
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

  for (int i = 0; i < self->rows; i++)
    for (int j = 0; j < self->cols; j++) {
      void* n = plus(self->data[i][j].data, other->data[i][j].data);
      self->data[i][j].data = n;
    }

  return self;
}

static void* Matrix_IArithmetic_subtract(void* const _self, const void* _other) {
  Matrix* const self = _self;
  const Matrix* other = _other;

  if (self->rows != other->rows || self->cols != other->cols)
    error(ERR_VALUE("Expected two matrices of the same size."))

  for (int i = 0; i < self->rows; i++)
    for (int j = 0; j < self->cols; j++) {
      void* n = minus(self->data[i][j].data, other->data[i][j].data);
      self->data[i][j].data = n;
    }

  return self;
}

static void* Matrix_IArithmetic_plus(const void* const _self, const void* _other) {
  const Matrix* const self = _self;
  const Matrix* other = _other;

  if (self->rows != other->rows || self->cols != other->cols)
    error(ERR_VALUE("Expected two matrices of the same size."))

  Matrix* m = new(matrix, self->rows, self->cols);

  for (int i = 0; i < self->rows; i++)
    for (int j = 0; j < self->cols; j++)
      m->data[i][j].data = plus(self->data[i][j].data, other->data[i][j].data);

  return m;
}

static void* Matrix_IArithmetic_minus(const void* const _self, const void* _other) {
  const Matrix* const self = _self;
  const Matrix* other = _other;

  if (self->rows != other->rows || self->cols != other->cols)
    error(ERR_VALUE("Expected two matrices of the same size."))

  Matrix* m = new(matrix, self->rows, self->cols);

  for (int i = 0; i < self->rows; i++)
    for (int j = 0; j < self->cols; j++)
      m->data[i][j].data = minus(self->data[i][j].data, other->data[i][j].data);

  return m;
}

static const IArithmetic _matrix_i_arithmetic = {
  .magic = I_ARITHMETIC,
  .add = Matrix_IArithmetic_add,
  .subtract = Matrix_IArithmetic_subtract,
  .plus = Matrix_IArithmetic_plus,
  .minus = Matrix_IArithmetic_minus
};

static const Interface _matrix_interfaces = {
  (void*)(&_matrix_i_arithmetic),
  NULL
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

  const Matrix* const self = _self;

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
      self->data[i][j].data = value;
    }
  }
}

void* scalarMultiply(const void* const _self, const void* scalar, void* (*f)(void*, void*)) {
  error(ERR_NOTIMPLEMENTED)
}
void* scalarMMultiply(const void* const _self, const void* _other, void* (*f)(void*, void*)) {
  error(ERR_NOTIMPLEMENTED)
}
void* mMultiply(const void* const _self, const void* _other) {
  error(ERR_NOTIMPLEMENTED)
}
void* mInverse(const void* const _self) {
  error(ERR_NOTIMPLEMENTED)
}
void* mTranspose(const void* const _self) {
  error(ERR_NOTIMPLEMENTED)
}
