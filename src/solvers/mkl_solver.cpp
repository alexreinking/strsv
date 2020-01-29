#include "solvers.h"
#include <mkl.h>

namespace solvers {

  void mkl_solver(Matrix &L, Vector &x) {
    cblas_strsv(CblasColMajor, CblasLower, CblasNoTrans, CblasUnit,
                x.size(), L.data(), x.size(), x.data(), 1);
  }

}// namespace solvers