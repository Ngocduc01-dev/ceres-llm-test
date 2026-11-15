// FILE: u0270_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0270, PathP1) {
  ceres::internal::ConcurrentQueue<int> queue;
  queue.StopWaiters();
}
