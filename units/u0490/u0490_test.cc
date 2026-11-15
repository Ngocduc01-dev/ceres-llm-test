// FILE: u0490_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0490, PathP1) {
  int arg_0 = 1;
  ceres::internal::ThreadTokenProvider target(arg_0);
  target.ThreadTokenProvider(1);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0490, PathP2) {
  int arg_0 = 1;
  ceres::internal::ThreadTokenProvider target(arg_0);
  target.ThreadTokenProvider(1);
}
