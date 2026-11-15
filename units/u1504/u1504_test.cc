// FILE: u1504_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END
TEST(u1504_Test, TC1_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.ZoomPhase(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1504_Test, TC2_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.ZoomPhase(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1504_Test, TC3_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.ZoomPhase(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1504_Test, TC4_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.ZoomPhase(nullptr, nullptr, nullptr, nullptr, nullptr);
}
