// FILE: u1005_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"
#include "ceres/line_search.h"
#include "ceres/map_util.h"

// P1: START -> 1 -> END
TEST(ResetTimeStatisticsTest, TC1_CallsTarget) {
  LineSearchFunction object{};
  object.ResetTimeStatistics();
}

