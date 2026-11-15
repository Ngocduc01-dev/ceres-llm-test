// FILE: u0477_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_for.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0477, PathP1) {
  std::mutex & arg_1{}
  ceres::internal::MakeConditionalLock(1, arg_1);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0477, PathP2) {
  std::mutex & arg_1{}
  ceres::internal::MakeConditionalLock(1, arg_1);
}
