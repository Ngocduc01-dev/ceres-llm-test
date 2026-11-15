// FILE: u1307_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/schur_complement_solver.cc"

// P1: START -> 1 -> END
TEST(u1307_Test, TC1_CallsTarget) {
  ceres::internal::(anonymous)::BlockRandomAccessSparseMatrixAdapter target{};
  target.RightMultiplyAndAccumulate(nullptr, nullptr);
}
