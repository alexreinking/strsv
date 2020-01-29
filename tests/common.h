#ifndef TESTS_COMMON_H
#define TESTS_COMMON_H

#include "solvers.h"
#include <functional>

using Solver = std::function<void(Matrix &, Vector &)>;

Matrix create_random_L(size_t n);
Vector create_random_b(size_t n);
bool relatively_close(const Vector &correct, const Vector &other);

#endif
