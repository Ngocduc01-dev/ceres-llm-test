// FILE: u1308_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/schur_complement_solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1308, TC1_CallsTarget) {
  Vector x{};
  Vector y{};
  ceres::internal::(anonymous)::BlockRandomAccessDiagonalMatrixAdapter object{};
  object.RightMultiplyAndAccumulate(x, y);
}
