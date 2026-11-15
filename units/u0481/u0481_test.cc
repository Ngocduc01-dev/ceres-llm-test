// FILE: u0481_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
TEST(Unit_u0481, LowerBound) { double state[1]={}; ceres::internal::ParameterBlock target(state,1,0); target.LowerBound(0); }
