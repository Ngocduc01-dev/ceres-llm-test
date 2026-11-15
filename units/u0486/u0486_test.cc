// FILE: u0486_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0486, PathP1) {
  ceres::internal::SetSummaryFinalCost<double>(nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0486, PathP2) {
  ceres::internal::SetSummaryFinalCost<double>(nullptr);
}
