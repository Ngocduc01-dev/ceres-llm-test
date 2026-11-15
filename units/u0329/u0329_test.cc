// FILE: u0329_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LinearLeastSquaresProblemCtor, DefaultConstruct) {
  ceres::internal::LinearLeastSquaresProblem problem;
  (void)problem;
}
