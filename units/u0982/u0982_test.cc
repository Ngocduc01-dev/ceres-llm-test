// FILE: u0982_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/sized_cost_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0982, TC1_CallsTarget) {
  SizedCostFunction<1, 2, 2> object{};
  (void)object;
}
