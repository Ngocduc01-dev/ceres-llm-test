// FILE: u1148_test.cc
#include "gtest/gtest.h"
#include "ceres/context.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1148, TC1_CallsTarget) {
  ceres::Context object{};
  object.Create();
}
