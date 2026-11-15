// FILE: u0295_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0295, PathP1) {
  ceres::internal::ExecutionSummary* object = nullptr;
  object->statistics();
}
