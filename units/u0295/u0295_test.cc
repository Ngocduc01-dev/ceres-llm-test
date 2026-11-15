// FILE: u0295_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"

TEST(Unit_u0295, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::internal::ExecutionSummary* object = nullptr;
  object->statistics();
}
