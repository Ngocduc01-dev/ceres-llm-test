// FILE: u0362_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0362, PathP1) {
  ceres::internal::ParameterBlock target;
  target.SetVarying();
}
