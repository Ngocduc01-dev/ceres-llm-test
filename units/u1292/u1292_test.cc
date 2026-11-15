// FILE: u1292_test.cc
#include "gtest/gtest.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1292, TC1_CallsTarget) {
  std::string event_name{};
  ceres::internal::EventLogger object{};
  object.AddEvent(event_name);
}
