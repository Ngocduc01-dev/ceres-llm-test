// FILE: u1520_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/line_search_preprocessor.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1520_Test, TC1_CallsTarget) {
  ceres::internal::LineSearchPreprocessor target{};
  target.Preprocess(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1520_Test, TC2_CallsTarget) {
  ceres::internal::LineSearchPreprocessor target{};
  target.Preprocess(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1520_Test, TC3_CallsTarget) {
  ceres::internal::LineSearchPreprocessor target{};
  target.Preprocess(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1520_Test, TC4_CallsTarget) {
  ceres::internal::LineSearchPreprocessor target{};
  target.Preprocess(nullptr, nullptr, nullptr);
}
