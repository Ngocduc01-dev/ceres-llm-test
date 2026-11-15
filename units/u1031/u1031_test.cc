// FILE: u1031_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// P1: START -> 1 -> END
TEST(PopTest, TC1_CallsTarget) {
  ConcurrentQueue object{};
  object.Pop(nullptr);
}

