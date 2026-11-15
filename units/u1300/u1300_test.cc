// FILE: u1300_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/callbacks.h"

// P1: START -> 1 -> END
TEST(u1300_Test, TC1_CallsTarget) {
  ceres::internal::LoggingCallback target{};
  target.operator()(nullptr);
}

// P2: START -> 1 -> END
TEST(u1300_Test, TC2_CallsTarget) {
  ceres::internal::LoggingCallback target{};
  target.operator()(nullptr);
}

// P3: START -> 1 -> END
TEST(u1300_Test, TC3_CallsTarget) {
  ceres::internal::LoggingCallback target{};
  target.operator()(nullptr);
}

// P4: START -> 1 -> END
TEST(u1300_Test, TC4_CallsTarget) {
  ceres::internal::LoggingCallback target{};
  target.operator()(nullptr);
}
