// FILE: u1031_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1031, TC1_CallsTarget) {
  ceres::internal::ConcurrentQueue object{};
  object.Pop(nullptr);
}
