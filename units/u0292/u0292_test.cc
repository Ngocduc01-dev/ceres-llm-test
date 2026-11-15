// FILE: u0292_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluation_callback.h"

TEST(Unit_u0292, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::EvaluationCallback* object = nullptr;
  object->~EvaluationCallback();
}
