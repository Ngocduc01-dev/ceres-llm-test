// FILE: u0422_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0422, PathP1) {
  int arg_0 = 1;
  ceres::internal::ThreadTokenProvider target(arg_0);
  target.Release(1);
}
