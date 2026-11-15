// FILE: u1048_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1048, TC1_CallsTarget) {
  ceres::internal::ConcurrentQueue object{};
  object.Wait(nullptr);
}
