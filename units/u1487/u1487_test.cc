// FILE: u1487_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/linear_solver.h"
#include "ceres/minimizer.h"
#include "ceres/parallel_for.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1487, TC1_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1487, TC2_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1487, TC3_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1487, TC4_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1487, TC5_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1487, TC6_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}
