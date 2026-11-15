// FILE: u0271_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0271, PathP1) {
  ceres::internal::ConcurrentQueue<int> queue;
  queue.EnableWaiters();
}
