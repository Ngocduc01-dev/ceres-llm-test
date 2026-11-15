// FILE: u0956_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver.h"
#include "ceres/minimizer.h"

// P1: START -> 1 -> END
TEST(RunCallbacksTest, TC1_CallsTarget) {
  Minimizer object{};
  Minimizer::Options & options a0{};
  IterationSummary & iteration_summary a1{};
  object.RunCallbacks(a0, a1, nullptr);
}

// P2: START -> 1 -> END
TEST(RunCallbacksTest, TC2_CallsTarget) {
  Minimizer object{};
  Minimizer::Options & options a0{};
  IterationSummary & iteration_summary a1{};
  object.RunCallbacks(a0, a1, nullptr);
}

// P3: START -> 1 -> END
TEST(RunCallbacksTest, TC3_CallsTarget) {
  Minimizer object{};
  Minimizer::Options & options a0{};
  IterationSummary & iteration_summary a1{};
  object.RunCallbacks(a0, a1, nullptr);
}

