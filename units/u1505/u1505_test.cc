// FILE: u1505_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END
TEST(u1505_Test, TC1_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.BracketingPhase(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1505_Test, TC2_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.BracketingPhase(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1505_Test, TC3_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.BracketingPhase(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1505_Test, TC4_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.BracketingPhase(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
