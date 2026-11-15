// FILE: u1048_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// P1: START -> 1 -> END
TEST(WaitTest, TC1_CallsTarget) {
  ConcurrentQueue object{};
  object.Wait(nullptr);
}

