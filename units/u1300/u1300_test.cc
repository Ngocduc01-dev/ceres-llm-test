// FILE: u1300_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/callbacks.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1300, TC1_CallsTarget) {
  )(const IterationSummary summary{};
  ceres::internal::LoggingCallback object{};
  object(summary);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1300, TC2_CallsTarget) {
  )(const IterationSummary summary{};
  ceres::internal::LoggingCallback object{};
  object(summary);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1300, TC3_CallsTarget) {
  )(const IterationSummary summary{};
  ceres::internal::LoggingCallback object{};
  object(summary);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1300, TC4_CallsTarget) {
  )(const IterationSummary summary{};
  ceres::internal::LoggingCallback object{};
  object(summary);
}
