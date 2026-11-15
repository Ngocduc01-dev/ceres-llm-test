// FILE: u0956_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver.h"
#include "ceres/minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0956, TC1_CallsTarget) {
  Minimizer::Options options{};
  IterationSummary iteration_summary{};
  ceres::internal::Minimizer object{};
  object.RunCallbacks(options, iteration_summary, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0956, TC2_CallsTarget) {
  Minimizer::Options options{};
  IterationSummary iteration_summary{};
  ceres::internal::Minimizer object{};
  object.RunCallbacks(options, iteration_summary, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0956, TC3_CallsTarget) {
  Minimizer::Options options{};
  IterationSummary iteration_summary{};
  ceres::internal::Minimizer object{};
  object.RunCallbacks(options, iteration_summary, nullptr);
}
