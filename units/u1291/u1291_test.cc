// FILE: u1291_test.cc
#include "gtest/gtest.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1291_Test, TC1_CallsTarget) {
  ceres::internal::EventLogger target{};
}
