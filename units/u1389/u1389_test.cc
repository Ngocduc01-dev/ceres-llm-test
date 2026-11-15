// FILE: u1389_test.cc
#include "gtest/gtest.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1389, TC1_CallsTarget) {
  ceres::internal::EventLogger object{};
  object.~EventLogger();
}
