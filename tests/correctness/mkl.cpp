#include <gtest/gtest.h>

#include "common.h"
#include "mkl_solver.h"

TEST(SolverTest, mkl_solver) {
  auto L = create_random_L(472);
  auto b = create_random_b(472);

  auto correct_x = L.triangularView<Eigen::Lower>().solve(b).eval();

  auto x = b;
  solvers::mkl_solver(L, x);
  ASSERT_PRED2(relatively_close, correct_x, x);
}
