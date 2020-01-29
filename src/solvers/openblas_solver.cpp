#include "openblas_solver.h"
#include <cblas.h>

namespace solvers {

  void openblas_solver(Matrix &L, Vector &x) {
    cblas_strsv(CblasColMajor, CblasLower, CblasNoTrans, CblasUnit,
                x.size(), L.data(), x.size(), x.data(), 1);
  }

}// namespace solvers