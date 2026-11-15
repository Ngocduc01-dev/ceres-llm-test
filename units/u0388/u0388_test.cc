// FILE: u0388_test.cc
#include "gtest/gtest.h"
#include "ceres/preprocessor.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(PreprocessedProblemConstructorTest, DefaultConstructor) {
  ceres::internal::PreprocessedProblem preprocessed_problem;
  (void)preprocessed_problem;
}
