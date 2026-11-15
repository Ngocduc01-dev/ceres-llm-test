// FILE: u1447_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver.h"
#include "ceres/evaluator.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"
#include "ceres/line_search_direction.h"
#include "ceres/line_search_minimizer.h"
#include "ceres/minimizer.h"

// P1: START -> 1 -> END
TEST(u1447_Test, TC1_CallsTarget) {
  ceres::internal::LineSearchMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1447_Test, TC2_CallsTarget) {
  ceres::internal::LineSearchMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1447_Test, TC3_CallsTarget) {
  ceres::internal::LineSearchMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1447_Test, TC4_CallsTarget) {
  ceres::internal::LineSearchMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}
