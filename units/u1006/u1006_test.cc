// FILE: u1006_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"
#include "ceres/line_search.h"
#include "ceres/map_util.h"

// P1: START -> 1 -> END
TEST(TimeStatisticsTest, TC1_CallsTarget) {
  LineSearchFunction object{};
  double a0[5] = {};
  double a1[5] = {};
  object.TimeStatistics(a0, a1);
}

