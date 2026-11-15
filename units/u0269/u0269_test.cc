// FILE: u0269_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0269, PathP1) {
  ceres::internal::ConcurrentQueue<int> queue;
  queue.Push(1);
}
