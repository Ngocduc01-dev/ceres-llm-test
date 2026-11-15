// FILE: u1308_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/schur_complement_solver.cc"

// P1: START -> 1 -> END
TEST(u1308_Test, TC1_CallsTarget) {
  ceres::internal::(anonymous)::BlockRandomAccessDiagonalMatrixAdapter target{};
  target.RightMultiplyAndAccumulate(nullptr, nullptr);
}
