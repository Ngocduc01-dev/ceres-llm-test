// FILE: u0865_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0865, TC1_CallsTarget) {
  ceres::IterationCallback object{};
  object.~IterationCallback();
}
