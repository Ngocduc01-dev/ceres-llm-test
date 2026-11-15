// FILE: u0491_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0491, PathP1) {
  ceres::internal::ThreadTokenProvider target;
  target.Acquire();
}
