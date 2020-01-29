#include "common.h"
#include <cfloat>
#include <random>

Matrix create_random_L(size_t n) {
  Matrix L{n, n};

  static std::random_device rd;
  static std::default_random_engine gen(rd());
  static std::uniform_real_distribution<float> dist(0, 1);

  // Fill L with a lower-triangular, column-major, unit matrix.
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < j; i++) {
      L(i, j) = 0.0f;
    }
    L(j, j) = 1.0f;
    for (int i = j + 1; i < n; i++) {
      L(i, j) = dist(gen);
    }
  }

  return L;
}

Vector create_random_b(size_t n) {
  Vector b{n};
  b.setRandom();
  return b;
}

bool relatively_close(const Vector &correct, const Vector &other) {
  float x_y = 0.0f;
  float y = 0.0f;
  int n = correct.size();
  for (int i = 0; i < n; ++i) {
    float diff = (other[i] - correct[i]);
    x_y += diff * diff;
    y += correct[i] * correct[i];
  }
  return sqrtf(x_y / y) < (3.0f * n * n) * FLT_EPSILON;
}