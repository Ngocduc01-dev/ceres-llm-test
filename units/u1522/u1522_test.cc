// FILE: u1522_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END
TEST(u1522_Test, TC1_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.DoSearch(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1522_Test, TC2_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.DoSearch(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1522_Test, TC3_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.DoSearch(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1522_Test, TC4_CallsTarget) {
  ceres::internal::WolfeLineSearch target{};
  target.DoSearch(nullptr, nullptr, nullptr, nullptr);
}
