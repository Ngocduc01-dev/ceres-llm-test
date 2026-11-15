// FILE: u0293_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0293, PathP1) {
  ceres::internal::Evaluator* object = nullptr;
  object->Statistics();
}
