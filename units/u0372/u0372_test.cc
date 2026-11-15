// FILE: u0372_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0372, PathP1) { double value[1] = {0}; ceres::internal::ParameterBlock target(value, 1, 0); target.mutable_residual_blocks(); }
