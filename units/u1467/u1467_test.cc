// FILE: u1467_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/callbacks.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1467, TC1_CallsTarget) {
  )(const IterationSummary arg0{};
  ceres::internal::StateUpdatingCallback object{};
  object(arg0);
}
