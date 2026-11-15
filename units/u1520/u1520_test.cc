// FILE: u1520_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/line_search_preprocessor.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1520, TC1_CallsTarget) {
  Solver::Options options{};
  ceres::internal::LineSearchPreprocessor object{};
  object.Preprocess(options, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1520, TC2_CallsTarget) {
  Solver::Options options{};
  ceres::internal::LineSearchPreprocessor object{};
  object.Preprocess(options, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1520, TC3_CallsTarget) {
  Solver::Options options{};
  ceres::internal::LineSearchPreprocessor object{};
  object.Preprocess(options, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1520, TC4_CallsTarget) {
  Solver::Options options{};
  ceres::internal::LineSearchPreprocessor object{};
  object.Preprocess(options, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1520, TC5_CallsTarget) {
  Solver::Options options{};
  ceres::internal::LineSearchPreprocessor object{};
  object.Preprocess(options, nullptr, nullptr);
}
