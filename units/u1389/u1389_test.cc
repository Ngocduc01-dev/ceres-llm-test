// FILE: u1389_test.cc
#include "gtest/gtest.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1389_Test, TC1_CallsTarget) {
  ceres::internal::EventLogger* target = new ceres::internal::EventLogger{};
  target->~EventLogger();
}
