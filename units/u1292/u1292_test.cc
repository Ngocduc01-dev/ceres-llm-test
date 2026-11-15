// FILE: u1292_test.cc
#include "gtest/gtest.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1292_Test, TC1_CallsTarget) {
  ceres::internal::EventLogger target{};
  target.AddEvent(nullptr);
}
