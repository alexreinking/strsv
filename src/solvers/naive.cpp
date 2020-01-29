#include "naive.h"

namespace solvers {

  void naive(Matrix &L, Vector &x) {
    int n = x.size();
    for (int j = 0; j < n; ++j) {
      for (int i = j + 1; i < n; ++i) {
        x[i] -= x[j] * L(i, j);
      }
    }
  }

}// namespace solvers