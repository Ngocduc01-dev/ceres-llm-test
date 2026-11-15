// FILE: u1399_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1399, TC1_CallsTarget) {
  Program program{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.IsOrderingValid(program, ordering, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1399, TC2_CallsTarget) {
  Program program{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.IsOrderingValid(program, ordering, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1399, TC3_CallsTarget) {
  Program program{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.IsOrderingValid(program, ordering, nullptr);
}
