// FILE: u1306_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/gradient_checker.h"

// P1: START -> 1 -> END
TEST(u1306_Test, TC1_CallsTarget) {
  ceres::GradientChecker target{};
  target.Probe(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1306_Test, TC2_CallsTarget) {
  ceres::GradientChecker target{};
  target.Probe(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1306_Test, TC3_CallsTarget) {
  ceres::GradientChecker target{};
  target.Probe(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1306_Test, TC4_CallsTarget) {
  ceres::GradientChecker target{};
  target.Probe(nullptr, nullptr, nullptr);
}
