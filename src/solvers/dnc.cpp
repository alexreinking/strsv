#include "dnc.h"
#include <cblas.h>

#define BLK (8)

namespace solvers {

  static void base_case(int n, const float *L, int lda, float *x) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        x[i] -= x[j] * L[i + j * lda];
      }
    }
  }

  static void update(int n, const float *L, int lda, float *x) {
    if (n <= BLK) {
      base_case(n, L, lda, x);
    } else {
      const auto split = n / 2;

      // Upper triangle -- reads L(:k,:k), x(:k); writes x(:k)
      update(split, L, lda, x);

      // Rectangle -- reads L(k:,:k), x(:k); writes x(k:)
      cblas_sgemv(CblasColMajor, CblasNoTrans, n - split, split, -1.f, L + split, lda,
                  x, 1, 1.f, x + split, 1);

      // Right triangle -- reads L(k:,k:), x(k:); writes x(k:)
      update(n - split, L + lda * split + split, lda, x + split);
    }
  }

  void dnc(Matrix &L, Vector &x) {
    size_t n = x.size();
    update(n, L.data(), n, x.data());
  }

}// namespace solvers
