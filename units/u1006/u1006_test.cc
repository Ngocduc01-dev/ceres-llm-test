// FILE: u1006_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"
#include "ceres/line_search.h"
#include "ceres/map_util.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1006, TC1_CallsTarget) {
  ceres::internal::LineSearchFunction object{};
  object.TimeStatistics(nullptr, nullptr);
}
