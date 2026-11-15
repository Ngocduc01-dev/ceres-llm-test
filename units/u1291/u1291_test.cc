// FILE: u1291_test.cc
#include "gtest/gtest.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1291, TC1_CallsTarget) {
  std::string logger_name{};
  ceres::internal::EventLogger object{};
  (void)object;
}
