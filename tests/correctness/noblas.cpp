#include <gtest/gtest.h>
#include <iostream>

#include "blocked.h"
#include "common.h"
#include "naive.h"

TEST(SolverTest, naive) {
  auto L = create_random_L(472);
  auto b = create_random_b(472);

  auto correct_x = L.triangularView<Eigen::Lower>().solve(b).eval();

  auto x = b;
  solvers::naive(L, x);
  ASSERT_PRED2(relatively_close, correct_x, x);
}

TEST(SolverTest, blocked) {
  auto L = create_random_L(472);
  auto b = create_random_b(472);

  auto correct_x = L.triangularView<Eigen::Lower>().solve(b).eval();

  auto x = b;
  solvers::blocked(L, x);
  ASSERT_PRED2(relatively_close, correct_x, x);
}
