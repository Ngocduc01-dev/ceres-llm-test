// FILE: u0292_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluation_callback.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0292, PathP1) {
  ceres::EvaluationCallback* object = nullptr;
  object->~EvaluationCallback();
}
