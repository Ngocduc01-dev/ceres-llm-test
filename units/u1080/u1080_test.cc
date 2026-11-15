// FILE: u1080_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1080, TC1_CallsTarget) {
  ceres::internal::SparseMatrixPreconditionerWrapper object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr);
}
