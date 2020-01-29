#include "blocked.h"

namespace solvers {

  typedef float v8sf __attribute__((vector_size(32), aligned(1)));

  /**
   * Performs an in-place triangular solve.
   * @param n - dimension of L and x. Must be a positive multiple of 8.
   * @param L - n x n, column-major, unit-diagonal, dense, lower-triangular matrix
   * @param lda - stride of outer dimension of L (ie. distance between columns)
   * @param x - dense n x 1 vector: as input: b in (Lx = b); as output: x.
   */
  void update_blocked(int n, const float *L, int lda, float *x) {
    // Strategy: divide L into n x 8, (n - 8) x 8, ..., 8x8 block-columns
    // Solve first 8 x-values using the top 8x8 triangle. Use these values
    // to update last n-8 b-values using the (n-8)x8 rectangle of L-values
    // below. This is made efficient by broadcasting x-values into registers,
    // then streaming L and b via FMA instructions.
    while (true) {
      // Handle triangle at top of block column
      {
        for (int j = 0; j < 8; ++j) {
          for (int i = j + 1; i < 8; ++i) {
            x[i] -= x[j] * L[i + lda * j];
          }
        }
      }

      // Last iteration doesn't have a rectangle
      n -= 8;
      if (n <= 0) {
        return;
      }

      // We have now solved 8 values of x with the triangle.
      // Broadcast these into vectors for upcoming FMA.
      v8sf x_solved[8];
      for (int i = 0; i < 8; i++) {
        x_solved[i] = _mm256_broadcast_ss(&x[i]);
      }

      // Advance L and x. L now points to top of rectangle
      // in block-column; x now points to the unsolved part.
      L += 8;
      x += 8;

      // Update unsolved part of x using n x 8 rectangle of L
      {
        for (int i = 0; i < n; i += 8) {
          // Load 8 unsolved values
          v8sf x_i = _mm256_loadu_ps(&x[i]);

          // Load 8x8 block of L
          v8sf Lc[8];
          for (int j = 0; j < 8; j++) {
            Lc[j] = _mm256_loadu_ps(&L[i + lda * j]);
          }

          // Update unsolved values. This compiles to 8 FMAs.
          for (int j = 0; j < 8; j++) {
            x_i -= x_solved[j] * Lc[j];
          }

          // Write updated values back to x
          _mm256_storeu_ps(&x[i], x_i);
        }
      }

      // Advance L to the top of triangle in next block-column
      L += lda * 8;
    }
  }

  void blocked(Matrix &Lm, Vector &xm) {
    int n = xm.size();
    int lda = n;

    float *L = Lm.data();
    float *x = xm.data();

    update_blocked(n, L, lda, x);
  }

}// namespace solvers
