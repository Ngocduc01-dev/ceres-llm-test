// FILE: u1391_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1391, TC1_CallsTarget) {
  int id{};
  ceres::internal::CreateLinearLeastSquaresProblemFromId(id);
}
