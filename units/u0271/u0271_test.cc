// FILE: u0271_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

TEST(Unit_u0271, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::internal::ConcurrentQueue<int> queue;
  queue.EnableWaiters();
}
